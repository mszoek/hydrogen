#ifndef HFS_H
#define HFS_H

#include <hw/types.h>

#ifdef KERNEL_HFS
#include <fs/gpt.h>
#endif

typedef UInt32        FourCharCode;
typedef FourCharCode  OSType;
typedef UInt32 HFSCatalogNodeID;
typedef UInt32 HFSCatalogNodeID;
typedef UInt16 UniChar;

enum BTreeTypes{
    kHFSBTreeType           =   0,      // control file
    kUserBTreeType          = 128,      // user btree type starts from 128
    kReservedBTreeType      = 255
};

enum {
    kBTLeafNode       = -1,
    kBTIndexNode      =  0,
    kBTHeaderNode     =  1,
    kBTMapNode        =  2
};

enum {
    kBTBadCloseMask           = 0x00000001,
    kBTBigKeysMask            = 0x00000002,
    kBTVariableIndexKeysMask  = 0x00000004
};

enum {
    kHFSPlusFolderRecord        = 0x0001,
    kHFSPlusFileRecord          = 0x0002,
    kHFSPlusFolderThreadRecord  = 0x0003,
    kHFSPlusFileThreadRecord    = 0x0004
};

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

typedef struct {
  SInt16              v;
  SInt16              h;
} __attribute__((packed, aligned(1))) Point;

typedef struct {
  SInt16              top;
  SInt16              left;
  SInt16              bottom;
  SInt16              right;
} __attribute__((packed, aligned(1))) Rect;

typedef struct {
  OSType    fileType;           /* The type of the file */
  OSType    fileCreator;        /* The file's creator */
  UInt16    finderFlags;
  Point     location;           /* File's location in the folder. */
  UInt16    reservedField;
} __attribute__((packed, aligned(1))) FileInfo;

typedef struct {
  SInt16    reserved1[4];
  UInt16    extendedFinderFlags;
  SInt16    reserved2;
  SInt32    putAwayFolderID;
} __attribute__((packed, aligned(1))) ExtendedFileInfo;

typedef struct {
  Rect      windowBounds;       /* The position and dimension of the */
                                /* folder's window */
  UInt16    finderFlags;
  Point     location;           /* Folder's location in the parent */
                                /* folder. If set to {0, 0}, the Finder */
                                /* will place the item automatically */
  UInt16    reservedField;
} __attribute__((packed, aligned(1))) FolderInfo;

typedef struct {
  Point     scrollPosition;     /* Scroll position (for icon views) */
  SInt32    reserved1;
  UInt16    extendedFinderFlags;
  SInt16    reserved2;
  SInt32    putAwayFolderID;
} __attribute__((packed, aligned(1))) ExtendedFolderInfo;

typedef struct {
    UInt16  length;
    UniChar unicode[255];
} __attribute__((packed, aligned(1))) HFSUniStr255;

typedef struct {
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
} __attribute__((packed, aligned(1))) HFSPlusBSDInfo;

typedef struct {
   UInt32                  startBlock;
   UInt32                  blockCount;
} HFSPlusExtentDescriptor;

typedef HFSPlusExtentDescriptor HFSPlusExtentRecord[8];

typedef struct {
   UInt64                  logicalSize;
   UInt32                  clumpSize;
   UInt32                  totalBlocks;
   HFSPlusExtentRecord     extents;
} HFSPlusForkData;

typedef struct {
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
} __attribute__((packed, aligned(1))) HFSPlusCatalogFile;

typedef struct {
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
} HFSPlusVolumeHeader;

typedef struct {
   UInt16              keyLength;
   HFSCatalogNodeID    parentID;
   HFSUniStr255        nodeName;
} __attribute__((packed)) HFSPlusCatalogKey;

typedef struct {
    UInt32    fLink;
    UInt32    bLink;
    SInt8     kind;
    UInt8     height;
    UInt16    numRecords;
    UInt16    reserved;
} __attribute__((packed, aligned(1))) BTNodeDescriptor;

typedef struct {
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
} __attribute__((packed, aligned(1))) BTHeaderRec;

#ifdef KERNEL_HFS

class HierarchicalFileSystem
{
public:
    HierarchicalFileSystem(Partition *part);
    virtual ~HierarchicalFileSystem();

    bool mount();
    bool unmount();
    bool isMounted();

private:
    Partition partition; // where this fs lives
    bool mounted;

    UInt64 catalogStartSector;
    UInt64 catalogEndSector;
};

#endif // KERNEL_HFS
#endif // HFS_H
