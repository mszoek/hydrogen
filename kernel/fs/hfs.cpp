/*
 * H2 HFS+ Filesystem Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#define KERNEL_HFS
#include <kernel.h>
#include <kstdio.h>
#include <vmem.h>
#include <hw/byteswap.h>
#include <fs/hfs.h>

#define ntohl(x) bswap32(x)
#define ntohs(x) bswap16(x)
#define htonl(x) bswap32(x)
#define htons(x) bswap16(x)

// our file descriptor table. slot = fd number.
fdMapType fdMap[FD_MAX];

int vacantFD()
{
    int i=0;
    for( ; i < FD_MAX; ++i)
        if(fdMap[i].entry == 0)
        {
            fdMap[i].entry = (void *)(-1);
            return i;
        }
    return -1;
}

HierarchicalFileSystem::HierarchicalFileSystem(Partition *p)
{
    if(verbose)
        kprintf("fs/HierarchicalFileSystem: 0x%x\n", this);

    memcpy((char *)&partition, (char *)p, sizeof(partition));
    catalogStartSector = catalogEndSector = 0;
    mounted = false;
}

HierarchicalFileSystem::~HierarchicalFileSystem()
{
}

bool HierarchicalFileSystem::mount()
{
    if(readVolumeHeader())
    {
        mounted = true;
        return true;
    }
    return false;
}

bool HierarchicalFileSystem::unmount()
{
    mounted = false;
    return true;
}

bool HierarchicalFileSystem::isMounted()
{
    return mounted;
}

bool HierarchicalFileSystem::readVolumeHeader()
{
    // allocate a buffer
    UInt16 *buf = (UInt16 *)malloc(8192);

    // read the volume header from the first block
    AHCIController *ahci = partition.getController();
    hbaPort *port = ahci->getPort(partition.getPort());
    ahci->read(port, buf, partition.getStartLBA()+2, sizeof(HFSPlusVolumeHeader)/512+1);

    HFSPlusVolumeHeader *vhdr = (HFSPlusVolumeHeader *)buf;
    if(vhdr->signature != 0x2B48) // 'H+'
    {
        kprintf("Invalid HFS+ signature - not mounting\n");
        free(buf);
        return false;
    }
    blockSize = ntohl(vhdr->blockSize);
    catalogStartSector = ntohl(vhdr->catalogFile.extents[0].startBlock)
        * (blockSize / 512) + partition.getStartLBA();
    catalogEndSector = (ntohl(vhdr->catalogFile.extents[0].blockCount)
        * (blockSize / 512)) + catalogStartSector;

    kprintf("HFS+: %d files, %d folders. %d / %d blocks free. Block size: %d\n",
        ntohl(vhdr->fileCount), ntohl(vhdr->folderCount),
        ntohl(vhdr->freeBlocks), ntohl(vhdr->totalBlocks),
        blockSize);

    free(buf);
    return true;
}

void *HierarchicalFileSystem::searchCatalog(const char *path, UInt16 kind)
{
    HFSPlusCatalogKey key;

    // allocate a buffer
    UInt16 *buf = (UInt16 *)malloc(8192);

    AHCIController *ahci = partition.getController();
    hbaPort *port = ahci->getPort(partition.getPort());
    ahci->read(port, buf, catalogStartSector, 16);

    BTHeaderRec *bthdrrec = (BTHeaderRec *)((UInt64)buf+sizeof(BTNodeDescriptor));
    int leafpos = ntohl(bthdrrec->firstLeafNode) * ntohs(bthdrrec->nodeSize);
    BTNodeDescriptor *btnodedesc = (BTNodeDescriptor *)((UInt64)buf+leafpos);

    // offset in words of the first catalog record pointer in 'buf'
    int pos = (leafpos + ntohs(bthdrrec->nodeSize)) / 2 - 1;
    int pathlen = strlen((char *)path);
    HFSUniStr255 unipath;
    int i;
    for(i = 0; i < strlen((char *)path); ++i)
    {
        if(i > 254)
            break;
        unipath.unicode[i] = htons(path[i]);
    }
    unipath.length = htons(i);

    for(int i=1; i <= ntohs(btnodedesc->numRecords); ++i)
    {
        // offset of record in bytes from start of node
        int offset = ntohs(buf[pos--]) + leafpos;
        // len = difference from offset of next record in bytes from start of node.
        int len = (leafpos + ntohs(buf[pos])) - offset;
        if(len == 0)
            continue;

        HFSPlusCatalogKey *catkey = (HFSPlusCatalogKey *)(&buf[offset/2]);
        UInt16 type = ntohs(buf[(offset+2+ntohs(catkey->keyLength))/2]);

        if(type != kind || unipath.length != catkey->nodeName.length)
            continue; // not what we want

        if(memcmp((char *)&unipath.unicode, (char *)&catkey->nodeName.unicode, pathlen))
            continue; // not a match

        HFSPlusCatalogFile *catrec = (HFSPlusCatalogFile *)malloc(sizeof(HFSPlusCatalogFile));
        memcpy((char *)catrec, (char *)((UInt64)buf+offset+2+ntohs(catkey->keyLength)), sizeof(HFSPlusCatalogFile));
        free(buf);
        return catrec;
    }

    free(buf);
    return 0;
}

int HierarchicalFileSystem::open(const char *path)
{
    if(path == 0 || *path == 0)
        return -1;

    HFSPlusCatalogFile *catfile = (HFSPlusCatalogFile *)searchCatalog(path, kHFSPlusFileRecord);
    if(catfile == 0)
        return -1;

    int fd = vacantFD();
    if(fd >= 0)
    {
        fdMap[fd].entry = catfile;
        fdMap[fd].fdtype = FDTYPE_CATFILE;
        return fd;
    }
    free(catfile);
    return -1;
}

void HierarchicalFileSystem::close(int fd)
{
    if(fd < 0 || fd >= FD_MAX)
        return;
    if(fdMap[fd].entry != 0 && fdMap[fd].entry != (void *)(-1))
    {
        free(fdMap[fd].entry);
        fdMap[fd].entry = 0;
        fdMap[fd].fdtype = FDTYPE_EMPTY;
    }
}

int HierarchicalFileSystem::read(int fd, UInt8 *buf, int len)
{
    if(fd < 0 || fd >= FD_MAX)
        return -1;
    if(fdMap[fd].entry == 0 || fdMap[fd].entry == (void *)(-1))
        return -1;
    if(fdMap[fd].fdtype != FDTYPE_CATFILE)
        return -1;

    AHCIController *ahci = partition.getController();
    hbaPort *port = ahci->getPort(partition.getPort());

    HFSPlusCatalogFile *cf = (HFSPlusCatalogFile *)fdMap[fd].entry;
    int bytesread = 0;
    int extent = 0;

    if(bswap64(cf->dataFork.logicalSize) < len)
        len = bswap64(cf->dataFork.logicalSize); // can't read more than we have!

    UInt16 *dbuf = (UInt16 *)malloc(256);
    while(bytesread < len && extent < 8)
    {
        if(cf->dataFork.extents[extent].startBlock == 0)
            continue;

        UInt64 sector = ntohl(cf->dataFork.extents[extent].startBlock) * (blockSize / 512) + partition.getStartLBA();
        UInt64 count = ntohl(cf->dataFork.extents[extent].blockCount) * (blockSize / 512);

        // only need to read one sector?
        if(len <= 512)
        {
            ahci->read(port, dbuf, sector, 1);
            memcpy((char *)buf, (char *)dbuf, len);
            bytesread = len;
            break;
        }

        // how many sectors do we need to read?
        UInt64 desired = (len - bytesread) / 512 + 1;

        if(desired > count)
        {
            // want more than this extent has. Read it all and move on.
            ahci->read(port, (UInt16 *)((UInt64)buf+bytesread), sector, count);
            bytesread += (count * 512);
            ++extent;
        } else {
            // what we want is within the extent. Read all but last sector.
            ahci->read(port, (UInt16 *)((UInt64)buf+bytesread), sector, desired - 1);
            bytesread += (desired - 1) * 512;
            ahci->read(port, dbuf, sector+desired-1, 1);
            memcpy((char *)(buf+bytesread), (char *)dbuf, len - bytesread);
            bytesread += len-bytesread;
            break;
        }
    }

    free(dbuf);
    return bytesread;
}

int HierarchicalFileSystem::stat(char *path, struct stat *s)
{
    if(path == 0 || *path == 0 || s == 0)
        return -1;

    HFSPlusCatalogFile *cf = (HFSPlusCatalogFile *)searchCatalog(path, kHFSPlusFileRecord);
    if(cf == 0)
        return -1;

    s->st_dev = 0x0800;
    s->st_ino = bswap32(cf->permissions.special.iNodeNum);
    s->st_mode = 0x10000 | bswap16(cf->permissions.fileMode);
    s->st_nlink = 0;
    s->st_uid = bswap32(cf->permissions.ownerID);
    s->st_gid = bswap32(cf->permissions.groupID);
    s->st_rdev = 0;
    s->st_size = bswap64(cf->dataFork.logicalSize);
    s->st_blksize = blockSize;
    s->st_blocks = 0;

    for(int i = 0; i < 8; ++i)
    {
        if(cf->dataFork.extents[i].startBlock != 0)
        {
            UInt64 count = ntohl(cf->dataFork.extents[i].blockCount) * (blockSize/512);
            s->st_blocks += count;
        }
    }

    s->st_atime = bswap32(cf->accessDate);
    s->st_mtime = bswap32(cf->contentModDate);
    s->st_ctime = bswap32(cf->attributeModDate);

    return 0;
}
