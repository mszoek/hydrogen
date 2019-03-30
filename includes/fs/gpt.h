#ifndef GPT_H
#define GPT_H

#include <hw/types.h>
#include <hw/ata.h>

// GPT lives at LBA 1
typedef struct _GPTHeader
{
    UInt8 signature[8]; // must contain "EFI PART"
    UInt8 revision[4];    // should be 0x00000100 (1.0)
    UInt32 hdrSize;     // little endian, usually 0x5C
    UInt32 crcHeader;
    UInt32 rsv0;        // must be 0
    UInt32 curLBALo;
    UInt32 curLBAHi;
    UInt32 backupLBALo;
    UInt32 backupLBAHi;
    UInt32 firstUsableLBALo;
    UInt32 firstUsableLBAHi;
    UInt32 lastUsableLBALo;
    UInt32 lastUsableLBAHi;
    UInt8 diskGUID[16];
    UInt32 partEntryLBALo;  // starting LBA of partition entries
    UInt32 partEntryLBAHi;
    UInt32 nrPartEntries;
    UInt32 sizePartEntry;   // usually 0x80
    UInt32 crcEntries;
    // rest of the sector must be 0's. 420 for a 512 byte sector.
} GPTHeader;

// Partition entries are LBAs 2-33
typedef struct _GPTEntry
{
    UInt8 typeGUID[16];
    UInt8 partGUID[16];
    UInt32 startLBALo;
    UInt32 startLBAHi;
    UInt32 endLBALo;
    UInt32 endLBAHi;
    UInt32 flagsLo;
    UInt32 flagsHi;
    UInt16 partName[36]; // UTF-16LE code units
} GPTEntry;

typedef enum
{
    ePlatformRequired = 1,
    eEFIShouldIgnore = 2,
    eLegacyBootable = 4
} PartFlags;


typedef struct _TypeGUIDEntry
{
    char *strGUID;
    UInt8 GUID[16];
    char *name;
} TypeGUIDEntry;

class GUIDPartitionTable
{
public:
    static void stringifyGUID(UInt8 *guid, char *buf);
    static void unstringifyGUID(char *guid, UInt8 *buf);

    GUIDPartitionTable(AHCIController *ahci, int port); // read table from specified disk
    virtual ~GUIDPartitionTable();

    bool isValid(); // true if we read a valid GPT


private:
    TypeGUIDEntry *getPartType(char *guid);
    
    bool gptValid;
    GPTHeader header;
    GPTEntry parts[32]; // we will only support 32 partitions per disk for now
    TypeGUIDEntry typeGUIDs[2] = {
        {"48465300-0000-11AA-AA11-00306543ECAC",
        {0x00,0x53,0x46,0x48,0x00,0x00,0xAA,0x11,0xAA,0x11,0x00,0x30,0x65,0x43,0xEC,0xAC},
        "HFS/HFS+"},
        {"C12A7328-F81F-11D2-BA4B-00A0C93EC93B",
        {0x28,0x73,0x2A,0xC1,0x1F,0xF8,0xD2,0x11,0xBA,0x4B,0x00,0xA0,0xC9,0x3E,0xC9,0x3B},
        "EFI System"}
    };
    int nrTypeGUIDs;
};

#endif // GPT_H