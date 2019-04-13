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

HierarchicalFileSystem::HierarchicalFileSystem(Partition *p)
{
    if(verbose)
        kprintf("fs/HierarchicalFileSystem(%s): 0x%x\n", p->getGUIDA(), this);
    memcpy((char *)&partition, (char *)p, sizeof(partition));

    // allocate a buffer
    UInt16 *buf = (UInt16 *)malloc(8192);
    if(buf)
        buf = (UInt16 *)vmm->remap((UInt64)buf, 8192);

    // read the volume header from the first block
    AHCIController *ahci = p->getController();
    hbaPort *port = ahci->getPort(p->getPort());
    ahci->read(port, buf, p->getStartLBA()+2, sizeof(HFSPlusVolumeHeader)/512+1);

    HFSPlusVolumeHeader *vhdr = (HFSPlusVolumeHeader *)buf;
    catalogStartSector = ntohl(vhdr->catalogFile.extents[0].startBlock)
        * (ntohl(vhdr->blockSize) / 512) + p->getStartLBA();
    catalogEndSector = (ntohl(vhdr->catalogFile.extents[0].blockCount)
        * (ntohl(vhdr->blockSize) / 512)) + catalogStartSector;

    if(debug)
    {
        kprintf("Block Size: %d File Count: %d\n", ntohl(vhdr->blockSize),
            ntohl(vhdr->fileCount));

        kprintf("Catalog File start: %x length: %x Sectors: %x - %x\n",
            ntohl(vhdr->catalogFile.extents[0].startBlock),
            ntohl(vhdr->catalogFile.extents[0].blockCount),
            catalogStartSector, catalogEndSector);
    }
   
    ahci->read(port, buf, catalogStartSector, 16);
    BTHeaderRec *bthdrrec = (BTHeaderRec *)((UInt64)buf+sizeof(BTNodeDescriptor));

    if(debug)
    {
        kprintf("BTHR Depth: %d Root: %x Leaves: %d First Leaf: %x Last Leaf: %x\n",
            ntohs(bthdrrec->treeDepth), ntohl(bthdrrec->rootNode),
            ntohl(bthdrrec->leafRecords), ntohl(bthdrrec->firstLeafNode),
            ntohl(bthdrrec->lastLeafNode));
        kprintf("BTHR Node Size: %d Max Key: %d Nodes: %d Free: %d: Reserved: %x\n",
            ntohs(bthdrrec->nodeSize), ntohs(bthdrrec->maxKeyLength),
            ntohl(bthdrrec->totalNodes), ntohl(bthdrrec->freeNodes),
            ntohs(bthdrrec->reserved1));
        kprintf("BTHR Clump Size: %d Type: %d Key Compare: %d Attrs: %x\n",
            ntohl(bthdrrec->clumpSize), bthdrrec->btreeType, bthdrrec->keyCompareType,
            ntohl(bthdrrec->attributes));
    }

    int leafpos = ntohl(bthdrrec->firstLeafNode) * ntohs(bthdrrec->nodeSize);
    // is the offset more than a sector?
    // int advance = (leafpos / 512);
    // ssector += advance;
    // get offset into buf
    // leafpos = (leafpos - 512*advance) % 512;
    // ahci->read(port, buf, p->getStartLBA() + ssector, 8);
    BTNodeDescriptor *btnodedesc = (BTNodeDescriptor *)((UInt64)buf+leafpos); 

    if(debug)
        kprintf("BTND FLink: %x BLink: %x Kind: %d Height: %d Records: %d\n",
            ntohl(btnodedesc->fLink), ntohl(btnodedesc->bLink), btnodedesc->kind,
            btnodedesc->height, ntohs(btnodedesc->numRecords));

    // offset in words of the first catalog record pointer in 'buf'
    int pos = (leafpos + ntohs(bthdrrec->nodeSize)) / 2 - 1;

    for(int i=1; i<=ntohs(btnodedesc->numRecords); ++i)
    {
        char asciiName[256];

        // offset of record in bytes from start of node
        int offset = ntohs(buf[pos--]) + leafpos;
        // len = difference from offset of next record in bytes from start of node.
        int len = (leafpos + ntohs(buf[pos])) - offset;
        if(len == 0)
            continue;

        HFSPlusCatalogKey *catkey = (HFSPlusCatalogKey *)(&buf[offset/2]);
        UInt16 type = ntohs(buf[(offset+2+ntohs(catkey->keyLength))/2]);

        if(debug)
        {
            memset(asciiName, 0, sizeof(asciiName));
            for(int j=0; j<ntohs(catkey->nodeName.length); ++j)
            {
                UInt16 ch = ntohs(catkey->nodeName.unicode[j]) & 0xFF;
                asciiName[j]=ch;
            }
            kprintf("Rec: %d Type: %d Length: %d keyLength: %d Parent: %d nodeName: %s\n",
                i, type, len, ntohs(catkey->keyLength), ntohl(catkey->parentID), asciiName);
        }

        if(type == kHFSPlusFileRecord)
        {
            HFSPlusCatalogFile *catrec = (HFSPlusCatalogFile *)((UInt64)buf+offset+2+ntohs(catkey->keyLength));

            if(debug)
            {
                kprintf("Type: %d Created: %x Blocks: %d\n", ntohs(catrec->recordType),
                    ntohl(catrec->createDate), ntohl(catrec->dataFork.totalBlocks));
                for(int i=0; i<8; ++i)
                {
                    kprintf("Data Fork extents[%d] start: %d len: %d\n", i,
                        ntohl(catrec->dataFork.extents[i].startBlock),
                        ntohl(catrec->dataFork.extents[i].blockCount));
                }
            }
        }
    }

    free(buf);
}

HierarchicalFileSystem::~HierarchicalFileSystem()
{
}

bool HierarchicalFileSystem::mount()
{
    mounted = true;
    return true;
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