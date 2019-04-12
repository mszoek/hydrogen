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

    kprintf("Block Size: %d File Count: %d\n", ntohl(vhdr->blockSize),
        ntohl(vhdr->fileCount));

    kprintf("Catalog File start: %x  length: %x\n",
        ntohl(vhdr->catalogFile.extents[0].startBlock),
        ntohl(vhdr->catalogFile.extents[0].blockCount));

    int ssector = ntohl(vhdr->catalogFile.extents[0].startBlock)
        * (ntohl(vhdr->blockSize) / 512);
    int esector = (ntohl(vhdr->catalogFile.extents[0].blockCount)
        * (ntohl(vhdr->blockSize) / 512)) + ssector;

    kprintf("Sectors start: %d end: %d\n", ssector, esector);

    BTNodeDescriptor node;
    BTHeaderRec header;
    
    ahci->read(port, buf, p->getStartLBA()+ssector, 16);
    memcpy((char *)&header, (char*)buf+sizeof(BTNodeDescriptor), sizeof(header));
    BTHeaderRec *bthdrrec = &header;

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

    int leafpos = ntohl(bthdrrec->firstLeafNode) * ntohs(bthdrrec->nodeSize);
    // is the offset more than a sector?
    // int advance = (leafpos / 512);
    // ssector += advance;
    // get offset into buf
    // leafpos = (leafpos - 512*advance) % 512;
    // ahci->read(port, buf, p->getStartLBA() + ssector, 8);
    memcpy((char *)&node, (char *)((UInt64)buf+leafpos), sizeof(node));
    BTNodeDescriptor *btnodedesc = (BTNodeDescriptor *)&node;

    kprintf("BTND FLink: %x BLink: %x Kind: %d Height: %d Records: %d\n",
        ntohl(btnodedesc->fLink), ntohl(btnodedesc->bLink), btnodedesc->kind,
        btnodedesc->height, ntohs(btnodedesc->numRecords));

    for(int i=1; i<=ntohs(btnodedesc->numRecords); ++i)
    {
        char asciiName[256];
        HFSPlusCatalogKey catkey;

        // offset in words into buffer
        int pos = (leafpos + ntohs(bthdrrec->nodeSize)) / 2 - i;

        // offset of first record in bytes from start of node
        int offset = ntohs(buf[pos]) + leafpos;

        // offset in words into buffer
        --pos;

        // end of first record in bytes from start of node. calc length.
        int len = (leafpos + ntohs(buf[pos])) - offset;

        memcpy((char *)&catkey, (char *)(&buf[offset/2 - 1]), sizeof(catkey));

        for(int j=0; j<ntohs(catkey.nodeName.length); ++j)
        {
            UInt16 ch = ntohs(catkey.nodeName.unicode[j]) & 0xFF;
            asciiName[j]=ch;
        }
        kprintf("Rec: %d Length: %d keyLength: %d Parent: %d nodeName: %s\n",
            i, len, ntohs(catkey.keyLength), ntohl(catkey.parentID), asciiName);

        if(strcmp(asciiName,"kernel.bin") == 0)
        {
            kprintf("found kernel.bin!\n");
        //   memcpy(&catrec, &nodedata[offset+2+htons(catkey.keyLength)],
        //     len-htons(catkey.keyLength));
        //   found=1;
            break;
        }
    }

//   if(!found)
//   {
//     printf("kernel.bin not found!\n");
//     return -1;
//   }

//   printf("Type: %d Created: %x Blocks: %d\n", htons(catrec.recordType),
//     htonl(catrec.createDate), htonl(catrec.dataFork.totalBlocks));
//   for(i=0; i<8; ++i)
//   {
//     printf("Data Fork extents[%d] start: %d len: %d\n", i,
//       htonl(catrec.dataFork.extents[i].startBlock),
//       htonl(catrec.dataFork.extents[i].blockCount));
//   }


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