; HFS+ data structures needed to load the kernel image from
; the H2OS boot file system.
;
; https://developer.apple.com/legacy/library/technotes/tn/tn1150.html#//apple_ref/doc/uid/DTS10002989
;
; Zoe Knox 2017

HFSPMagic           equ   0x2b48    ; = H+ little endian

HFSPSignature       equ   0x6000
HFSPVersion         equ   HFSPSignature+2
HFSPFileCount       equ   HFSPVersion+32
HFSPStartupFile     equ   HFSPSignature+432

msg_hfs_sig_bad     db    "Bad HFS+ signature",0

;struct HFSPlusVolumeHeader {
;    UInt16              signature;
;    UInt16              version;
;    UInt32              attributes;
;    UInt32              lastMountedVersion;
;    UInt32              journalInfoBlock;
;
;    UInt32              createDate;
;    UInt32              modifyDate;
;    UInt32              backupDate;
;    UInt32              checkedDate;
;
;    UInt32              fileCount;
;    UInt32              folderCount;
;
;    UInt32              blockSize;
;    UInt32              totalBlocks;
;    UInt32              freeBlocks;
;
;    UInt32              nextAllocation;
;    UInt32              rsrcClumpSize;
;    UInt32              dataClumpSize;
;    HFSCatalogNodeID    nextCatalogID;
;
;    UInt32              writeCount;
;    UInt64              encodingsBitmap;
;
;    UInt32              finderInfo[8];
;
;    HFSPlusForkData     allocationFile;
;    HFSPlusForkData     extentsFile;
;    HFSPlusForkData     catalogFile;
;    HFSPlusForkData     attributesFile;
;    HFSPlusForkData     startupFile;
;};

;struct HFSPlusCatalogKey {
;    UInt16              keyLength;
;    HFSCatalogNodeID    parentID;
;    HFSUniStr255        nodeName;
;};

;struct HFSPlusForkData {
;    UInt64                  logicalSize;
;    UInt32                  clumpSize;
;    UInt32                  totalBlocks;
;    HFSPlusExtentRecord     extents;
;};
;typedef HFSPlusExtentDescriptor HFSPlusExtentRecord[8];

;struct HFSPlusExtentDescriptor {
;    UInt32                  startBlock;
;    UInt32                  blockCount;
;};
