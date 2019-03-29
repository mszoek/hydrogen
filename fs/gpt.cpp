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


GUIDPartitionTable::GUIDPartitionTable(AHCIController *ahci, int port)
{
    gptValid = false;
    UInt16 diskbuf[256];

    if(ahci == 0 || port < 0 || port > 32) return;

    hbaPort *p = ahci->getPort(port);
    memset((char *)diskbuf, 0, 512);
    if(! ahci->read(p, diskbuf, 1, 1)) // read header & part entries
    {
        kprintf("Disk read error\n");
        return;
    }
    memcpy((char *)&header, (char *)diskbuf, sizeof(header));

    char guid[40];
    stringifyGUID(header.diskGUID, guid);

    if(memcmp((char *)&header.signature,"EFI PART",8) == 0)
    {
        kprintf("Version %d.%d Header size %d CRC %8x LBA %d Backup %d\n",
        header.revision[2], header.revision[3], header.hdrSize, header.crcHeader, header.curLBALo, header.backupLBALo);
        kprintf("First LBA %d Last LBA %d GUID %s\nPartitions %d\n",
        header.firstUsableLBALo, header.lastUsableLBALo, guid, header.nrPartEntries);
        gptValid = true;
    }

    // FIXME: we could calculate the LBAs to read for the partition entries
    // from the partEntryLBA and firstUsableLBA fields in the header

    const char zeroGUID[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 2; ++i)
    {    
        if(! ahci->read(p, diskbuf, 2+i, 1)) // read header & part entries
        {
            kprintf("Disk read error\n");
            return;
        }

        if(memcmp((char *)diskbuf, (char *)zeroGUID, 16) == 0)
            continue;

        memcpy((char *)&parts[i], (char *)diskbuf, sizeof(GPTEntry));

        char partGUID[40], typeGUID[40];
        stringifyGUID(parts[i].partGUID, partGUID);
        stringifyGUID(parts[i].typeGUID, typeGUID);

        kprintf("Partition %d GUID %s\nType %s\nStart LBA %d End LBA %d  %s\n", i,
            partGUID, typeGUID, parts[i].startLBALo, parts[i].endLBALo, parts[i].partName);
    }

}

GUIDPartitionTable::~GUIDPartitionTable()
{
}

bool GUIDPartitionTable::isValid()
{
    return gptValid;
}

