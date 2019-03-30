#include <kernel.h>
#include <kstring.h>
#include <kstdio.h>
#include <kmem.h>
#include <fs/gpt.h>

/* convert a "middle endian" GPT GUID into a string for display */
void GUIDPartitionTable::stringifyGUID(UInt8 *guid, char *buf)
{
    if(buf == 0 || guid == 0) return;
    int z = 0;
    UInt16 digits;

    for(int q = 3; q >= 0; --q)
    {
        digits = hexdigit(guid[q]);
        buf[z++] = ((UInt8 *)&digits)[0];
        buf[z++] = ((UInt8 *)&digits)[1];
    }
    buf[z++] = '-';

    digits = hexdigit(guid[5]);
    buf[z++] = ((UInt8 *)&digits)[0];
    buf[z++] = ((UInt8 *)&digits)[1];

    digits = hexdigit(guid[4]);
    buf[z++] = ((UInt8 *)&digits)[0];
    buf[z++] = ((UInt8 *)&digits)[1];

    buf[z++] = '-';

    digits = hexdigit(guid[7]);
    buf[z++] = ((UInt8 *)&digits)[0];
    buf[z++] = ((UInt8 *)&digits)[1];
    
    digits = hexdigit(guid[6]);
    buf[z++] = ((UInt8 *)&digits)[0];
    buf[z++] = ((UInt8 *)&digits)[1];

    buf[z++] = '-';

    digits = hexdigit(guid[8]);
    buf[z++] = ((UInt8 *)&digits)[0];
    buf[z++] = ((UInt8 *)&digits)[1];

    digits = hexdigit(guid[9]);
    buf[z++] = ((UInt8 *)&digits)[0];
    buf[z++] = ((UInt8 *)&digits)[1];

    buf[z++] = '-';

    for(int q = 10; q < 16; ++q)
    {
        digits = hexdigit(guid[q]);
        buf[z++] = ((UInt8 *)&digits)[0];
        buf[z++] = ((UInt8 *)&digits)[1];
    }

    buf[z] = 0;
}

/* convert a string GUID into the 16 byte packed binary format */
void GUIDPartitionTable::unstringifyGUID(char *guid, UInt8 *buf)
{
    UInt32 a;
    UInt16 b;

    a = atoi16(guid);
    memcpy((char *)buf, (char *)&a, 4);
    b = atoi16(&guid[9]);
    memcpy((char *)buf+4, (char *)&b, 2);
    b = atoi16(&guid[14]);
    memcpy((char *)buf+6, (char *)&b, 2);
    b = atoi16(&guid[19]);
    int c = (b & 0xFF) << 8;
    b = b >> 8 | c;
    memcpy((char *)buf+8, (char *)&b, 2);
    int ch = guid[32];
    guid[32] = 0;
    a = atoi16(&guid[24]);
    asm("bswap %0" : "=r"(a) : "r"(a));
    memcpy((char *)buf+10, (char *)&a, 4);
    guid[32] = ch;
    b = atoi16(&guid[32]);
    c = (b & 0xFF) << 8;
    b = b >> 8 | c;
    memcpy((char *)buf+14, (char *)&b, 2);
}

TypeGUIDEntry *GUIDPartitionTable::getPartType(char *guid)
{
    for(int i = 0; i < nrTypeGUIDs; ++i)
        if(memcmp(guid, (char *)typeGUIDs[i].GUID, 16) == 0)
            return &typeGUIDs[i];
    return 0;
}

GUIDPartitionTable::GUIDPartitionTable(AHCIController *ahci, int port)
{
    gptValid = false;
    nrTypeGUIDs = sizeof(typeGUIDs) / sizeof(TypeGUIDEntry);

    if(ahci == 0 || port < 0 || port > 32)
        return;
    hbaPort *p = ahci->getPort(port);

    UInt16 *diskbuf = (UInt16 *)malloc(4096);
    memset((char *)diskbuf, 0, 512);

    // read header and make sure it's valid
    int result = ahci->read(p, diskbuf, 1, 1);
    memcpy((char *)&header, (char *)diskbuf, sizeof(header));
    free(diskbuf);

    if(!result) 
    {
        kprintf("Disk read error\n"); // FIXME: identify device
        return;
    }

    if(memcmp((char *)&header.signature,"EFI PART",8) == 0)
    {
        if(verbose)
        {
            char guid[40];
            stringifyGUID(header.diskGUID, guid);

            kprintf("Version %d.%d Header size %d CRC %8x LBA %d Backup %d\n",
            header.revision[2], header.revision[3], header.hdrSize, header.crcHeader, header.curLBALo, header.backupLBALo);
            kprintf("First LBA %d Last LBA %d GUID %s\nPartitions %d\n",
            header.firstUsableLBALo, header.lastUsableLBALo, guid, header.nrPartEntries);
        }
        gptValid = true;
    }

    if(!gptValid)
        return;

    // FIXME: we could calculate the LBAs to read for the partition entries
    // from the partEntryLBA and firstUsableLBA fields in the header

    diskbuf = (UInt16 *)malloc(16384); // 16K for 32 512-byte sectors
    result = ahci->read(p, diskbuf, 2, 31); // read part entries
    if(!result) 
    {
        free(diskbuf);
        kprintf("Disk read error\n"); // FIXME: identify device
        return;
    }

    for(int i = 0; i < 32; ++i)
    {
        TypeGUIDEntry *t = getPartType((char *)diskbuf+sizeof(GPTEntry)*i);
        if(!t)
            continue;   // skip - we don't recognize the type

        memcpy((char *)&parts[i], (char *)diskbuf+sizeof(GPTEntry)*i, sizeof(GPTEntry));
        if(verbose)
        {
            char partGUID[40];

            stringifyGUID(parts[i].partGUID, partGUID);
            kprintf("Partition %d GUID %s\nType %s Start LBA %d End LBA %d\n", i,
                partGUID, t->name, parts[i].startLBALo, parts[i].endLBALo);
        }
    }
    free(diskbuf);
}

GUIDPartitionTable::~GUIDPartitionTable()
{
}

bool GUIDPartitionTable::isValid()
{
    return gptValid;
}

