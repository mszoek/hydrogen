#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>

typedef unsigned short UInt16;
typedef signed short SInt16;
typedef unsigned int UInt32;
typedef signed int SInt32;
typedef unsigned long long UInt64;
typedef signed char SInt8;
typedef unsigned char UInt8;

typedef UInt32 HFSCatalogNodeID;
typedef UInt16 UniChar;

struct HFSUniStr255 {
    UInt16  length;
    UniChar unicode[255];
} __attribute__((packed, aligned(1)));
typedef struct HFSUniStr255 HFSUniStr255;
typedef const  HFSUniStr255 *ConstHFSUniStr255Param;

struct BTNodeDescriptor {
    UInt32    fLink;
    UInt32    bLink;
    SInt8     kind;
    UInt8     height;
    UInt16    numRecords;
    UInt16    reserved;
} __attribute__((packed, aligned(1)));
typedef struct BTNodeDescriptor BTNodeDescriptor;

enum {
    kBTLeafNode       = -1,
    kBTIndexNode      =  0,
    kBTHeaderNode     =  1,
    kBTMapNode        =  2
};

struct BTHeaderRec {
    UInt16    treeDepth;
    UInt32    rootNode;
    UInt32    leafRecords;
    UInt32    firstLeafNode;
    UInt32    lastLeafNode;
    UInt16    nodeSize;
    UInt16    maxKeyLength;
    UInt32    totalNodes;
    UInt32    freeNodes;
    UInt16    reserved1;
    UInt32    clumpSize;      // misaligned
    UInt8     btreeType;
    UInt8     keyCompareType;
    UInt32    attributes;     // long aligned again
    UInt32    reserved3[16];
} __attribute__((packed, aligned(1)));
typedef struct BTHeaderRec BTHeaderRec;

enum BTreeTypes{
    kHFSBTreeType           =   0,      // control file
    kUserBTreeType          = 128,      // user btree type starts from 128
    kReservedBTreeType      = 255
};

enum {
    kBTBadCloseMask           = 0x00000001,
    kBTBigKeysMask            = 0x00000002,
    kBTVariableIndexKeysMask  = 0x00000004
};


struct HFSPlusExtentDescriptor {
    UInt32                  startBlock;
    UInt32                  blockCount;
};
typedef struct HFSPlusExtentDescriptor HFSPlusExtentDescriptor;
typedef HFSPlusExtentDescriptor HFSPlusExtentRecord[8];

struct HFSPlusForkData {
    UInt64                  logicalSize;
    UInt32                  clumpSize;
    UInt32                  totalBlocks;
    HFSPlusExtentRecord     extents;
} __attribute__((packed, aligned(1)));
typedef struct HFSPlusForkData HFSPlusForkData;


struct HFSPlusVolumeHeader {
    UInt16              signature;
    UInt16              version;
    UInt32              attributes;
    UInt32              lastMountedVersion;
    UInt32              journalInfoBlock;

    UInt32              createDate;
    UInt32              modifyDate;
    UInt32              backupDate;
    UInt32              checkedDate;

    UInt32              fileCount;
    UInt32              folderCount;

    UInt32              blockSize;
    UInt32              totalBlocks;
    UInt32              freeBlocks;

    UInt32              nextAllocation;
    UInt32              rsrcClumpSize;
    UInt32              dataClumpSize;
    HFSCatalogNodeID    nextCatalogID;

    UInt32              writeCount;
    UInt64              encodingsBitmap;

    UInt32              finderInfo[8];

    HFSPlusForkData     allocationFile;
    HFSPlusForkData     extentsFile;
    HFSPlusForkData     catalogFile;
    HFSPlusForkData     attributesFile;
    HFSPlusForkData     startupFile;
} __attribute__((packed, aligned(1)));
typedef struct HFSPlusVolumeHeader HFSPlusVolumeHeader;

struct HFSPlusBSDInfo {
    UInt32  ownerID;
    UInt32  groupID;
    UInt8   adminFlags;
    UInt8   ownerFlags;
    UInt16  fileMode;
    union {
        UInt32  iNodeNum;
        UInt32  linkCount;
        UInt32  rawDevice;
    } special;
} __attribute__((packed, aligned(1)));
typedef struct HFSPlusBSDInfo HFSPlusBSDInfo;

struct HFSPlusCatalogKey {
    UInt16              keyLength;
    HFSCatalogNodeID    parentID;
    HFSUniStr255        nodeName;
} __attribute__((packed, aligned(1)));
typedef struct HFSPlusCatalogKey HFSPlusCatalogKey;

enum {
    kHFSPlusFolderRecord        = 0x0001,
    kHFSPlusFileRecord          = 0x0002,
    kHFSPlusFolderThreadRecord  = 0x0003,
    kHFSPlusFileThreadRecord    = 0x0004
};

struct Point {
  SInt16              v;
  SInt16              h;
} __attribute__((packed, aligned(1)));
typedef struct Point  Point;

struct Rect {
  SInt16              top;
  SInt16              left;
  SInt16              bottom;
  SInt16              right;
} __attribute__((packed, aligned(1)));
typedef struct Rect   Rect;

/* OSType is a 32-bit value made by packing four 1-byte characters
   together. */
typedef UInt32        FourCharCode;
typedef FourCharCode  OSType;

/* Finder flags (finderFlags, fdFlags and frFlags) */
enum {
  kIsOnDesk       = 0x0001,     /* Files and folders (System 6) */
  kColor          = 0x000E,     /* Files and folders */
  kIsShared       = 0x0040,     /* Files only (Applications only) If */
                                /* clear, the application needs */
                                /* to write to its resource fork, */
                                /* and therefore cannot be shared */
                                /* on a server */
  kHasNoINITs     = 0x0080,     /* Files only (Extensions/Control */
                                /* Panels only) */
                                /* This file contains no INIT resource */
  kHasBeenInited  = 0x0100,     /* Files only.  Clear if the file */
                                /* contains desktop database resources */
                                /* ('BNDL', 'FREF', 'open', 'kind'...) */
                                /* that have not been added yet.  Set */
                                /* only by the Finder. */
                                /* Reserved for folders */
  kHasCustomIcon  = 0x0400,     /* Files and folders */
  kIsStationery   = 0x0800,     /* Files only */
  kNameLocked     = 0x1000,     /* Files and folders */
  kHasBundle      = 0x2000,     /* Files only */
  kIsInvisible    = 0x4000,     /* Files and folders */
  kIsAlias        = 0x8000      /* Files only */
};

/* Extended flags (extendedFinderFlags, fdXFlags and frXFlags) */
enum {
  kExtendedFlagsAreInvalid    = 0x8000, /* The other extended flags */
                                        /* should be ignored */
  kExtendedFlagHasCustomBadge = 0x0100, /* The file or folder has a */
                                        /* badge resource */
  kExtendedFlagHasRoutingInfo = 0x0004  /* The file contains routing */
                                        /* info resource */
};

struct FileInfo {
  OSType    fileType;           /* The type of the file */
  OSType    fileCreator;        /* The file's creator */
  UInt16    finderFlags;
  Point     location;           /* File's location in the folder. */
  UInt16    reservedField;
} __attribute__((packed, aligned(1)));
typedef struct FileInfo   FileInfo;

struct ExtendedFileInfo {
  SInt16    reserved1[4];
  UInt16    extendedFinderFlags;
  SInt16    reserved2;
  SInt32    putAwayFolderID;
} __attribute__((packed, aligned(1)));
typedef struct ExtendedFileInfo   ExtendedFileInfo;

struct FolderInfo {
  Rect      windowBounds;       /* The position and dimension of the */
                                /* folder's window */
  UInt16    finderFlags;
  Point     location;           /* Folder's location in the parent */
                                /* folder. If set to {0, 0}, the Finder */
                                /* will place the item automatically */
  UInt16    reservedField;
} __attribute__((packed, aligned(1)));
typedef struct FolderInfo   FolderInfo;

struct ExtendedFolderInfo {
  Point     scrollPosition;     /* Scroll position (for icon views) */
  SInt32    reserved1;
  UInt16    extendedFinderFlags;
  SInt16    reserved2;
  SInt32    putAwayFolderID;
} __attribute__((packed, aligned(1)));
typedef struct ExtendedFolderInfo   ExtendedFolderInfo;


struct HFSPlusCatalogFile {
    SInt16              recordType;
    UInt16              flags;
    UInt32              reserved1;
    HFSCatalogNodeID    fileID;
    UInt32              createDate;
    UInt32              contentModDate;
    UInt32              attributeModDate;
    UInt32              accessDate;
    UInt32              backupDate;
    HFSPlusBSDInfo      permissions;
    FileInfo            userInfo;
    ExtendedFileInfo    finderInfo;
    UInt32              textEncoding;
    UInt32              reserved2;

    HFSPlusForkData     dataFork;
    HFSPlusForkData     resourceFork;
} __attribute__((packed, aligned(1)));
typedef struct HFSPlusCatalogFile HFSPlusCatalogFile;

typedef UInt32 HFSCatalogNodeID;
enum {
    kHFSRootParentID            = 1,
    kHFSRootFolderID            = 2,
    kHFSExtentsFileID           = 3,
    kHFSCatalogFileID           = 4,
    kHFSBadBlockFileID          = 5,
    kHFSAllocationFileID        = 6,
    kHFSStartupFileID           = 7,
    kHFSAttributesFileID        = 8,
    kHFSRepairCatalogFileID     = 14,
    kHFSBogusExtentFileID       = 15,
    kHFSFirstUserCatalogNodeID  = 16
};

void printdata(UInt8* nodedata, int len)
{
  char ascii[20];
  int i,j=0;

  for(i=0,j=0; i<len; ++i)
  {
      if(j==0)
        printf("%04x ",i);
      printf("%02x ", nodedata[i]);
      ascii[j++] = isprint(nodedata[i]) ? nodedata[i] : '.';
      if(j > 15)
      {
        printf("%s\n",ascii);
        j=0;
      }
  }
}

int main(void)
{
  HFSPlusVolumeHeader vhdr;
  int fpos, ssector, esector, i, j, found=0;
  BTNodeDescriptor btnodedesc;
  BTHeaderRec bthdrrec;
  UInt16 offset = 0;
  UInt8 nodedata[8192]; // allow for 8K nodes, but we use 4K
  HFSPlusCatalogKey catkey;
  HFSPlusCatalogFile catrec;

  int fd = open("hd.img",O_RDWR);
  if(fd < 0) {
    perror("open");
    return -1;
  }

  fpos = lseek(fd, 1024, SEEK_SET);
  if(fpos != 1024) {
    perror("lseek");
  }

  read(fd, &vhdr, sizeof(vhdr));
  printf("Block Size: %d File Count: %d\n", ntohl(vhdr.blockSize),
    ntohl(vhdr.fileCount));

  printf("Catalog File start: %x  length: %x\n",
    ntohl(vhdr.catalogFile.extents[0].startBlock),
    ntohl(vhdr.catalogFile.extents[0].blockCount));

  printf("Startup File start: %d  length: %d\n",
    ntohl(vhdr.startupFile.extents[0].startBlock),
    ntohl(vhdr.startupFile.extents[0].blockCount));

  ssector = ntohl(vhdr.catalogFile.extents[0].startBlock)
    * (ntohl(vhdr.blockSize) / 512);
  esector = (ntohl(vhdr.catalogFile.extents[0].blockCount)
    * (ntohl(vhdr.blockSize) / 512)) + ssector;

  printf("Sectors start: %d (%d)  end: %d (%d)\n", ssector, ssector*512,
    esector, esector*512);

  fpos = lseek(fd, 512*ssector, SEEK_SET);
  read(fd, &btnodedesc, sizeof(btnodedesc));
  read(fd, &bthdrrec, sizeof(bthdrrec));

  printf("BTHR Depth: %d Root: %x Leaves: %d First Leaf: %x Last Leaf: %x\n",
    ntohs(bthdrrec.treeDepth),ntohl(bthdrrec.rootNode),
    ntohl(bthdrrec.leafRecords), ntohl(bthdrrec.firstLeafNode),
    ntohl(bthdrrec.lastLeafNode));
  printf("BTHR Node Size: %d Max Key: %d Nodes: %d Free: %d: Reserved: %x\n",
    ntohs(bthdrrec.nodeSize), ntohs(bthdrrec.maxKeyLength),
    ntohl(bthdrrec.totalNodes), ntohl(bthdrrec.freeNodes),
    ntohs(bthdrrec.reserved1));
  printf("BTHR Clump Size: %d Type: %d Key Compare: %d Attrs: %x\n",
    ntohl(bthdrrec.clumpSize), bthdrrec.btreeType, bthdrrec.keyCompareType,
    ntohl(bthdrrec.attributes));

  int leafpos = ntohl(bthdrrec.firstLeafNode) * ntohs(bthdrrec.nodeSize);
  lseek(fd, fpos+leafpos, SEEK_SET);
  read(fd, nodedata, htons(bthdrrec.nodeSize));
  memcpy(&btnodedesc, nodedata, sizeof(btnodedesc));

  printf("BTND FLink: %x BLink: %x Kind: %d Height: %d Records: %d\n",
    ntohl(btnodedesc.fLink), ntohl(btnodedesc.bLink), btnodedesc.kind,
    btnodedesc.height, ntohs(btnodedesc.numRecords));

  for(i=1; i<=ntohs(btnodedesc.numRecords); ++i)
  {
    int len;
    char asciiName[256];

    int pos = htons(bthdrrec.nodeSize) - i*2;
    offset = htons(*(UInt16*)(&nodedata[pos]));
    pos = htons(bthdrrec.nodeSize) - (i+1)*2;
    len = htons(*(UInt16*)(&nodedata[pos])) - offset;
    memcpy(&catkey, &nodedata[offset], len);

    for(int j=0; j<htons(catkey.nodeName.length); ++j)
    {
      UInt16 ch = htons(catkey.nodeName.unicode[j]) & 0xFF;
      asciiName[j]=ch;
    }
    printf("Rec: %d Length: %d keyLength: %d Parent: %d nodeName: %s\n",
      i, len, htons(catkey.keyLength), htonl(catkey.parentID), asciiName);

    if(strcasecmp(asciiName,"kernel.bin") == 0)
    {
      printf("found kernel.bin!\n");
      memcpy(&catrec, &nodedata[offset+2+htons(catkey.keyLength)],
        len-htons(catkey.keyLength));
      found=1;
      break;
    }
  }

  if(!found)
  {
    printf("kernel.bin not found!\n");
    return -1;
  }

  printf("Type: %d Created: %x\n", htons(catrec.recordType),
    htonl(catrec.createDate));
  printf("Data Fork blocks: %d extents[0] start: %d len: %d\n",
    htonl(catrec.dataFork.totalBlocks),
    htonl(catrec.dataFork.extents[0].startBlock),
    htonl(catrec.dataFork.extents[0].blockCount));

  memcpy(&vhdr.startupFile, &catrec.dataFork, sizeof(HFSPlusForkData));

  printf("Startup File start: %d  length: %d\n",
    ntohl(vhdr.startupFile.extents[0].startBlock),
    ntohl(vhdr.startupFile.extents[0].blockCount));

  fpos = lseek(fd, 1024, SEEK_SET);
  if(fpos != 1024)
  {
    printf("Error 1 writing startup file to vol header\n");
    return -1;
  }
  fpos = write(fd, &vhdr, sizeof(vhdr));
  if(fpos != sizeof(vhdr))
  {
    printf("Error 2 writing startup file to vol header\n");
    return -2;
  }

  close(fd);
  return 0;
}
