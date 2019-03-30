/*
 * H2 AHCI ATA/ATAPI Driver
 * Copyright (C) 2017-2019 Zoe Knox. All rights reserved.
 */

#ifndef ATA_H
#define ATA_H

#include <hw/types.h>

#define AHCI_BASE 0x800000 // 8 MB

#define SATA_SIG_ATA 0x00000101     // SATA drive
#define SATA_SIG_ATAPI 0xEB140101   // SATAPI drive
#define SATA_SIG_SEMB 0xC33C0101    // enclosure management bridge
#define SATA_SIG_PM 0x96690101      // port multiplier

#define AHCI_DEV_NULL   0
#define AHCI_DEV_SATA   1
#define AHCI_DEV_SEMB   2
#define AHCI_DEV_PM     3
#define AHCI_DEV_SATAPI 4

#define HBA_PORT_IPM_ACTIVE 1
#define HBA_PORT_DET_PRESENT 3

// ATA status bits
#define ATA_SR_BSY  0x80
#define ATA_SR_DRDY 0x40
#define ATA_SR_DF   0x20
#define ATA_SR_DSC  0x10
#define ATA_SR_DRQ  0x08
#define ATA_SR_CORR 0x04
#define ATA_SR_IDX  0x02
#define ATA_SR_ERR  0x01

// ATA error bits
#define ATA_ERR_BBK   0x80
#define ATA_ERR_UNC   0x40
#define ATA_ERR_MC    0x20
#define ATA_ERR_IDNF  0x10
#define ATA_ERR_MCR   0x08
#define ATA_ERR_ABRT  0x04
#define ATA_ERR_TK0NF 0x02
#define ATA_ERR_AMNF  0x01

// ATA commands
#define ATA_CMD_READ_PIO        0x20
#define ATA_CMD_READ_PIO_EXT    0x24
#define ATA_CMD_READ_DMA        0xC8
#define ATA_CMD_READ_DMA_EXT    0x25
#define ATA_CMD_WRITE_PIO       0x30
#define ATA_CMD_WRITE_PIO_EXT   0x34
#define ATA_CMD_WRITE_DMA       0xCA
#define ATA_CMD_WRITE_DMA_EXT   0x35
#define ATA_CMD_CACHE_FLUSH     0xE7
#define ATA_CMD_CACHE_FLUSH_EXT 0xEA
#define ATA_CMD_PACKET          0xA0
#define ATA_CMD_IDENTIFY_PACKET 0xA1
#define ATA_CMD_IDENTIFY        0xEC

// ATAPI commands
#define ATAPI_CMD_READ  0xA8
#define ATAPI_CMD_EJECT 0x1B

// HBA commands
#define PORT_CMD_ST (1 << 0)
#define PORT_CMD_FRE (1 << 4)
#define PORT_CMD_FR (1 << 14)
#define PORT_CMD_CR (1 << 15)

// SATA FIS types
typedef enum
{
    eFISTypeRegH2D    = 0x27, // Register FIS, host to device
    eFISTypeRegD2H    = 0x34, // Register FIS, device to host
    eFISTypeDMAAct    = 0x39, // DMA activate, device to host
    eFISTypeDMASetup  = 0x41, // DMA setup, bidirectional
    eFISTypeData      = 0x46, // data, bidirectional
    eFISTypeBIST      = 0x58, // activate BIST (self test), bidirectional
    eFISTypePIOSetup  = 0x5F, // PIO setup, bidirectional
    eFISTypeDevBits   = 0xA1  // Set device bts, device to host
} sataFISType;

typedef struct
{
    // dword 0
    UInt8 fisType;      // eFisTypeDevBits
    UInt8 rsv0:6;       // reserved
    UInt8 i:1;          // interrupt bit
    UInt8 rsv1:1;       // reserved
    UInt8 statusLo:3;   // status bits 2-0
    UInt8 rsv2:1;       // reserved
    UInt8 statusHi:3;   // status bits 5-3
    UInt8 rsv3:1;       // reserved
    UInt8 error;

    // dword 1
    UInt32 sact;        // SActive command bits 
} SataFISSetDevBits;

typedef struct
{
    // dword 0
    UInt8 fisType;      // eFisTypeRegH2D
    UInt8 portMult:4;   // port multiplier
    UInt8 rsv0:3;       // reserved
    UInt8 cc:1;         // 0 = control, 1 = command
    UInt8 command;      // command register
    UInt8 featureLo;    // feature register bits 7-0

    // dword 1
    UInt8 lba0;         // LBA register bits 7-0
    UInt8 lba1;         // LBA register bits 15-8
    UInt8 lba2;         // LBA register bits 23-16
    UInt8 device;

    // dword 2
    UInt8 lba3;         // LBA register bits 31-24
    UInt8 lba4;         // LBA register bits 39-32
    UInt8 lba5;         // LBA register bits 47-40
    UInt8 featureHi;    // feature register bits 15-8

    // dword 3
    UInt8 countLo;      // count register bits 7-0
    UInt8 countHi;      // count register bits 15-8
    UInt8 icc;          // isochronous command completion
    UInt8 control;      // control register

    // dword 4
    UInt8 rsv1[4];      // reserved
} SataFISRegH2D;

typedef struct
{
    // dword 0
    UInt8 fisType;      // eFisTypeRegD2H
    UInt8 portMult:4;   // port multiplier
    UInt8 rsv0:1;       // reserved
    UInt8 i:1;          // interrupt bit
    UInt8 rsv1:1;       // reserved
    UInt8 status;
    UInt8 error;

    // dword 1
    UInt8 lba0;         // LBA register bits 7-0
    UInt8 lba1;         // LBA register bits 15-8
    UInt8 lba2;         // LBA register bits 23-16
    UInt8 device;

    // dword 2
    UInt8 lba3;         // LBA register bits 31-24
    UInt8 lba4;         // LBA register bits 39-32
    UInt8 lba5;         // LBA register bits 47-40
    UInt8 rsv2;         // reserved

    // dword 3
    UInt8 countLo;      // count register bits 7-0
    UInt8 countHi;      // count register bits 15-8
    UInt8 rsv3[2];      // reserved

    // dword 4
    UInt8 rsv4[4];      // reserved
} SataFISRegD2H;

typedef struct
{
    // dword 0
    UInt8 fisType;      // eFisTypeData
    UInt8 portMult:4;   // port multiplier
    UInt8 rsv0:4;       // reserved
    UInt8 rsv1[2];      // reserved

    // dwords 1 - n
    UInt32 data[1];
} SataFISData;

typedef struct {
    // dword 0
    UInt8 fisType;      // eFisTypePIOSetup
    UInt8 portMult:4;   // port multiplier
    UInt8 rsv0:1;       // reserved
    UInt8 d:1;          // direction, 1 = device to host
    UInt8 i:1;          // interrupt bit
    UInt8 rsv1:1;       // reserved
    UInt8 status;
    UInt8 error;

    // dword 1
    UInt8 lba0;         // LBA register bits 7-0
    UInt8 lba1;         // LBA register bits 15-8
    UInt8 lba2;         // LBA register bits 23-16
    UInt8 device;

    // dword 2
    UInt8 lba3;         // LBA register bits 31-24
    UInt8 lba4;         // LBA register bits 39-32
    UInt8 lba5;         // LBA register bits 47-40
    UInt8 rsv2;         // reserved

    // dword 3
    UInt8 countLo;      // count register bits 7-0
    UInt8 countHi;      // count register bits 15-8
    UInt8 rsv3;         // reserved
    UInt8 eStatus;      // new value of status register

    // dword 4
    UInt16 tc;          // transfer count
    UInt8 rsv4[2];      // reserved

} SataFISPIOSetup;

typedef struct {
    // dword 0
    UInt8 fisType;      // eFisTypeDMASetup
    UInt8 portMult:4;   // port multiplier
    UInt8 rsv0:1;       // reserved
    UInt8 d:1;          // direction, 1 = device to host
    UInt8 i:1;          // interrupt bit
    UInt8 act:1;        // auto-activate specifies if DMA act FIS is needed
    UInt8 rsv1[2];      // reserved

    // dword 1 and 2
    UInt32 dmaBufferID[2]; // 64-bit DMA buffer ID

    // dword 3
    UInt32 rsv2;        // reserved

    // dword 4
    UInt32 dmaBufferOffset; // byte offset into buffer. bits 0-1 must = 0

    // dword 5
    UInt32 transferCount; // bytes to transfer. bit 0 must = 0

    // dword 6
    UInt32 rsv3;        // reserved
} SataFISDMASetup;

typedef volatile struct hbaPort_tag
{
    UInt32 clbLo;       // 0x00 command list base addr (1K aligned) bits 31-0
    UInt32 clbHi;       // 0x04 command list base addr bits 63-32
    UInt32 fbLo;        // 0x08 FIS base address, 256-byte aligned
    UInt32 fbHi;        // 0x0C FIS base address bits 63-32
    UInt32 is;          // 0x10 interrupt status
    UInt32 ie;          // 0x14 interrupt enable
    UInt32 cmd;         // 0x18 command & status
    UInt32 rsv0;
            // 0x1C reserved
    UInt32 tfd;         // 0x20 task file data
    UInt32 sig;         // 0x24 signature
    UInt32 ssts;        // 0x28 SATA status (SCR0: SStatus)
    UInt32 sctl;        // 0x2C SATA control (SCR2: SControl)   
    UInt32 serr;        // 0x30 SATA error (SCR1: Serror)
    UInt32 sact;        // 0x34 SATA active (SCR3: SActive)
    UInt32 ci;          // 0x38 command issue
    UInt32 sntf;        // 0x3C SATA notification (SCR4: SNotification)
    UInt32 fbs;         // 0x40 FIS-based switch control
    UInt32 rsv1[11];    // 0x44 - 0x6F Reserved
    UInt32 vendor[4];   // 0x70 - 0x7F Vendor specific
} hbaPort;

typedef struct
{
    // 0x00 to 0x2B, Generic Host Control
    UInt32 cap;         // 0x00 Host Capability
    UInt32 ghc;         // 0x04 Global Host Control
    UInt32 is;          // 0x08 Interrupt Status
    UInt32 pi;          // 0x0C Port Implemented
    UInt32 vs;          // 0x10 Version
    UInt32 cccCtl;      // 0x14 Command completion coalescing control
    UInt32 cccPorts;    // 0x18 Command completion coalescing ports
    UInt32 emLoc;       // 0x1C Enclosure Management Location
    UInt32 emCtl;       // 0x20 Enclosure Management Control
    UInt32 cap2;        // 0x24 Host Capabilities Extended
    UInt32 bohc;        // 0x28 BIOS/OS handoff control & status

    // 0x2C - 0x9F, Reserved
    UInt8 reserved[0xA0-0x2C];

    // 0xA0 - 0xFF, Vendor specific registers
    UInt8 vendor[0x100 - 0xA0];

    // 0x100 - 0x10FF, Port control registers
    hbaPort ports[32];   // 1 - 32
} hbaMem;

typedef struct
{
    // 0x00
    SataFISDMASetup dsFIS;
    UInt8 pad0[4];

    // 0x20
    SataFISPIOSetup psFIS;
    UInt8 pad1[12];

    // 0x40
    SataFISRegD2H rFIS;
    UInt8 pad2[4];

    // 0x58
    SataFISSetDevBits sdbFIS;

    // 0x60
    UInt8 uFIS[64];

    // 0xA0
    UInt8 rsv[0x100-0xA0];
} hbaFIS;

typedef struct
{
    // dword 0
    UInt8 cfl:5;        // command FIS length (dword) 2-16
    UInt8 a:1;          // ATAPI
    UInt8 w:1;          // write 0=D2H 1=H2D
    UInt8 p:1;          // prefetchable

    UInt8 r:1;          // reset
    UInt8 b:1;          // BIST
    UInt8 c:1;          // clear BSY on R_OK
    UInt8 rsv0:1;       // reserved
    UInt8 pmp:4;        // port multiplier port

    UInt16 prdtLen;     // phys region descriptor table len (entries)

    // dword 1
    volatile UInt32 prdbc; // phys region descriptor byte count transferred

    // dword 2 & 3
    UInt32 ctbaLo;      // command table descriptor base addr 31-0
    UInt32 ctbaHi;      // command table descriptor base addr 63-32

    // dword 4 - 7
    UInt32 rsv1[4];     // reserved
} hbaCmdHeader;

typedef struct
{
    UInt32 dbaLo;       // data base addr 31-0
    UInt32 dbaHi;       // data base addr 63-32
    UInt32 rsv0;        // reserved

    UInt32 dbc:22;      // byte count, 4M max
    UInt32 rsv1:9;      // reserved
    UInt32 i:1;         // interrupt when complete
} hbaPRDTEntry;

typedef struct
{
    // 0x00
    UInt8 cFIS[64];     // command FIS

    // 0x40
    UInt8 acmd[16];     // ATAPI cmd, 12 or 16 bytes
    
    // 0x50
    UInt8 rsv[48];      // reserved

    // 0x80
    hbaPRDTEntry prdtEntry[1];  // PRDT entries 0-65535
} hbaCmdTable;

typedef struct {
  struct {
    UInt16 Reserved1 : 1;
    UInt16 Retired3 : 1;
    UInt16 ResponseIncomplete : 1;
    UInt16 Retired2 : 3;
    UInt16 FixedDevice : 1;
    UInt16 RemovableMedia : 1;
    UInt16 Retired1 : 7;
    UInt16 DeviceType : 1;
  } GeneralConfiguration;
  UInt16 NumCylinders;
  UInt16 SpecificConfiguration;
  UInt16 NumHeads;
  UInt16 Retired1[2];
  UInt16 NumSectorsPerTrack;
  UInt16 VendorUnique1[3];
  UInt8  SerialNumber[20];
  UInt16 Retired2[2];
  UInt16 Obsolete1;
  UInt8  FirmwareRevision[8];
  UInt8  ModelNumber[40];
  UInt8  MaximumBlockTransfer;
  UInt8  VendorUnique2;
  struct {
    UInt16 FeatureSupported : 1;
    UInt16 Reserved : 15;
  } TrustedComputing;
  struct {
    UInt8  CurrentLongPhysicalSectorAlignment : 2;
    UInt8  ReservedByte49 : 6;
    UInt8  DmaSupported : 1;
    UInt8  LbaSupported : 1;
    UInt8  IordyDisable : 1;
    UInt8  IordySupported : 1;
    UInt8  Reserved1 : 1;
    UInt8  StandybyTimerSupport : 1;
    UInt8  Reserved2 : 2;
    UInt16 ReservedWord50;
  } Capabilities;
  UInt16 ObsoleteWords51[2];
  UInt16 TranslationFieldsValid : 3;
  UInt16 Reserved3 : 5;
  UInt16 FreeFallControlSensitivity : 8;
  UInt16 NumberOfCurrentCylinders;
  UInt16 NumberOfCurrentHeads;
  UInt16 CurrentSectorsPerTrack;
  UInt32  CurrentSectorCapacity;
  UInt8  CurrentMultiSectorSetting;
  UInt8  MultiSectorSettingValid : 1;
  UInt8  ReservedByte59 : 3;
  UInt8  SanitizeFeatureSupported : 1;
  UInt8  CryptoScrambleExtCommandSupported : 1;
  UInt8  OverwriteExtCommandSupported : 1;
  UInt8  BlockEraseExtCommandSupported : 1;
  UInt32  UserAddressableSectors;
  UInt16 ObsoleteWord62;
  UInt16 MultiWordDMASupport : 8;
  UInt16 MultiWordDMAActive : 8;
  UInt16 AdvancedPIOModes : 8;
  UInt16 ReservedByte64 : 8;
  UInt16 MinimumMWXferCycleTime;
  UInt16 RecommendedMWXferCycleTime;
  UInt16 MinimumPIOCycleTime;
  UInt16 MinimumPIOCycleTimeIORDY;
  struct {
    UInt16 ZonedCapabilities : 2;
    UInt16 NonVolatileWriteCache : 1;
    UInt16 ExtendedUserAddressableSectorsSupported : 1;
    UInt16 DeviceEncryptsAllUserData : 1;
    UInt16 ReadZeroAfterTrimSupported : 1;
    UInt16 Optional28BitCommandsSupported : 1;
    UInt16 IEEE1667 : 1;
    UInt16 DownloadMicrocodeDmaSupported : 1;
    UInt16 SetMaxSetPasswordUnlockDmaSupported : 1;
    UInt16 WriteBufferDmaSupported : 1;
    UInt16 ReadBufferDmaSupported : 1;
    UInt16 DeviceConfigIdentifySetDmaSupported : 1;
    UInt16 LPSAERCSupported : 1;
    UInt16 DeterministicReadAfterTrimSupported : 1;
    UInt16 CFastSpecSupported : 1;
  } AdditionalSupported;
  UInt16 ReservedWords70[5];
  UInt16 QueueDepth : 5;
  UInt16 ReservedWord75 : 11;
  struct {
    UInt16 Reserved0 : 1;
    UInt16 SataGen1 : 1;
    UInt16 SataGen2 : 1;
    UInt16 SataGen3 : 1;
    UInt16 Reserved1 : 4;
    UInt16 NCQ : 1;
    UInt16 HIPM : 1;
    UInt16 PhyEvents : 1;
    UInt16 NcqUnload : 1;
    UInt16 NcqPriority : 1;
    UInt16 HostAutoPS : 1;
    UInt16 DeviceAutoPS : 1;
    UInt16 ReadLogDMA : 1;
    UInt16 Reserved2 : 1;
    UInt16 CurrentSpeed : 3;
    UInt16 NcqStreaming : 1;
    UInt16 NcqQueueMgmt : 1;
    UInt16 NcqReceiveSend : 1;
    UInt16 DEVSLPtoReducedPwrState : 1;
    UInt16 Reserved3 : 8;
  } SerialAtaCapabilities;
  struct {
    UInt16 Reserved0 : 1;
    UInt16 NonZeroOffsets : 1;
    UInt16 DmaSetupAutoActivate : 1;
    UInt16 DIPM : 1;
    UInt16 InOrderData : 1;
    UInt16 HardwareFeatureControl : 1;
    UInt16 SoftwareSettingsPreservation : 1;
    UInt16 NCQAutosense : 1;
    UInt16 DEVSLP : 1;
    UInt16 HybridInformation : 1;
    UInt16 Reserved1 : 6;
  } SerialAtaFeaturesSupported;
  struct {
    UInt16 Reserved0 : 1;
    UInt16 NonZeroOffsets : 1;
    UInt16 DmaSetupAutoActivate : 1;
    UInt16 DIPM : 1;
    UInt16 InOrderData : 1;
    UInt16 HardwareFeatureControl : 1;
    UInt16 SoftwareSettingsPreservation : 1;
    UInt16 DeviceAutoPS : 1;
    UInt16 DEVSLP : 1;
    UInt16 HybridInformation : 1;
    UInt16 Reserved1 : 6;
  } SerialAtaFeaturesEnabled;
  UInt16 MajorRevision;
  UInt16 MinorRevision;
  struct {
    UInt16 SmartCommands : 1;
    UInt16 SecurityMode : 1;
    UInt16 RemovableMediaFeature : 1;
    UInt16 PowerManagement : 1;
    UInt16 Reserved1 : 1;
    UInt16 WriteCache : 1;
    UInt16 LookAhead : 1;
    UInt16 ReleaseInterrupt : 1;
    UInt16 ServiceInterrupt : 1;
    UInt16 DeviceReset : 1;
    UInt16 HostProtectedArea : 1;
    UInt16 Obsolete1 : 1;
    UInt16 WriteBuffer : 1;
    UInt16 ReadBuffer : 1;
    UInt16 Nop : 1;
    UInt16 Obsolete2 : 1;
    UInt16 DownloadMicrocode : 1;
    UInt16 DmaQueued : 1;
    UInt16 Cfa : 1;
    UInt16 AdvancedPm : 1;
    UInt16 Msn : 1;
    UInt16 PowerUpInStandby : 1;
    UInt16 ManualPowerUp : 1;
    UInt16 Reserved2 : 1;
    UInt16 SetMax : 1;
    UInt16 Acoustics : 1;
    UInt16 BigLba : 1;
    UInt16 DeviceConfigOverlay : 1;
    UInt16 FlushCache : 1;
    UInt16 FlushCacheExt : 1;
    UInt16 WordValid83 : 2;
    UInt16 SmartErrorLog : 1;
    UInt16 SmartSelfTest : 1;
    UInt16 MediaSerialNumber : 1;
    UInt16 MediaCardPassThrough : 1;
    UInt16 StreamingFeature : 1;
    UInt16 GpLogging : 1;
    UInt16 WriteFua : 1;
    UInt16 WriteQueuedFua : 1;
    UInt16 WWN64Bit : 1;
    UInt16 URGReadStream : 1;
    UInt16 URGWriteStream : 1;
    UInt16 ReservedForTechReport : 2;
    UInt16 IdleWithUnloadFeature : 1;
    UInt16 WordValid : 2;
  } CommandSetSupport;
  struct {
    UInt16 SmartCommands : 1;
    UInt16 SecurityMode : 1;
    UInt16 RemovableMediaFeature : 1;
    UInt16 PowerManagement : 1;
    UInt16 Reserved1 : 1;
    UInt16 WriteCache : 1;
    UInt16 LookAhead : 1;
    UInt16 ReleaseInterrupt : 1;
    UInt16 ServiceInterrupt : 1;
    UInt16 DeviceReset : 1;
    UInt16 HostProtectedArea : 1;
    UInt16 Obsolete1 : 1;
    UInt16 WriteBuffer : 1;
    UInt16 ReadBuffer : 1;
    UInt16 Nop : 1;
    UInt16 Obsolete2 : 1;
    UInt16 DownloadMicrocode : 1;
    UInt16 DmaQueued : 1;
    UInt16 Cfa : 1;
    UInt16 AdvancedPm : 1;
    UInt16 Msn : 1;
    UInt16 PowerUpInStandby : 1;
    UInt16 ManualPowerUp : 1;
    UInt16 Reserved2 : 1;
    UInt16 SetMax : 1;
    UInt16 Acoustics : 1;
    UInt16 BigLba : 1;
    UInt16 DeviceConfigOverlay : 1;
    UInt16 FlushCache : 1;
    UInt16 FlushCacheExt : 1;
    UInt16 Resrved3 : 1;
    UInt16 Words119_120Valid : 1;
    UInt16 SmartErrorLog : 1;
    UInt16 SmartSelfTest : 1;
    UInt16 MediaSerialNumber : 1;
    UInt16 MediaCardPassThrough : 1;
    UInt16 StreamingFeature : 1;
    UInt16 GpLogging : 1;
    UInt16 WriteFua : 1;
    UInt16 WriteQueuedFua : 1;
    UInt16 WWN64Bit : 1;
    UInt16 URGReadStream : 1;
    UInt16 URGWriteStream : 1;
    UInt16 ReservedForTechReport : 2;
    UInt16 IdleWithUnloadFeature : 1;
    UInt16 Reserved4 : 2;
  } CommandSetActive;
  UInt16 UltraDMASupport : 8;
  UInt16 UltraDMAActive : 8;
  struct {
    UInt16 TimeRequired : 15;
    UInt16 ExtendedTimeReported : 1;
  } NormalSecurityEraseUnit;
  struct {
    UInt16 TimeRequired : 15;
    UInt16 ExtendedTimeReported : 1;
  } EnhancedSecurityEraseUnit;
  UInt16 CurrentAPMLevel : 8;
  UInt16 ReservedWord91 : 8;
  UInt16 MasterPasswordID;
  UInt16 HardwareResetResult;
  UInt16 CurrentAcousticValue : 8;
  UInt16 RecommendedAcousticValue : 8;
  UInt16 StreamMinRequestSize;
  UInt16 StreamingTransferTimeDMA;
  UInt16 StreamingAccessLatencyDMAPIO;
  UInt32  StreamingPerfGranularity;
  UInt32  Max48BitLBA[2];
  UInt16 StreamingTransferTime;
  UInt16 DsmCap;
  struct {
    UInt16 LogicalSectorsPerPhysicalSector : 4;
    UInt16 Reserved0 : 8;
    UInt16 LogicalSectorLongerThan256Words : 1;
    UInt16 MultipleLogicalSectorsPerPhysicalSector : 1;
    UInt16 Reserved1 : 2;
  } PhysicalLogicalSectorSize;
  UInt16 InterSeekDelay;
  UInt16 WorldWideName[4];
  UInt16 ReservedForWorldWideName128[4];
  UInt16 ReservedForTlcTechnicalReport;
  UInt16 WordsPerLogicalSector[2];
  struct {
    UInt16 ReservedForDrqTechnicalReport : 1;
    UInt16 WriteReadVerify : 1;
    UInt16 WriteUncorrectableExt : 1;
    UInt16 ReadWriteLogDmaExt : 1;
    UInt16 DownloadMicrocodeMode3 : 1;
    UInt16 FreefallControl : 1;
    UInt16 SenseDataReporting : 1;
    UInt16 ExtendedPowerConditions : 1;
    UInt16 Reserved0 : 6;
    UInt16 WordValid : 2;
  } CommandSetSupportExt;
  struct {
    UInt16 ReservedForDrqTechnicalReport : 1;
    UInt16 WriteReadVerify : 1;
    UInt16 WriteUncorrectableExt : 1;
    UInt16 ReadWriteLogDmaExt : 1;
    UInt16 DownloadMicrocodeMode3 : 1;
    UInt16 FreefallControl : 1;
    UInt16 SenseDataReporting : 1;
    UInt16 ExtendedPowerConditions : 1;
    UInt16 Reserved0 : 6;
    UInt16 Reserved1 : 2;
  } CommandSetActiveExt;
  UInt16 ReservedForExpandedSupportandActive[6];
  UInt16 MsnSupport : 2;
  UInt16 ReservedWord127 : 14;
  struct {
    UInt16 SecuritySupported : 1;
    UInt16 SecurityEnabled : 1;
    UInt16 SecurityLocked : 1;
    UInt16 SecurityFrozen : 1;
    UInt16 SecurityCountExpired : 1;
    UInt16 EnhancedSecurityEraseSupported : 1;
    UInt16 Reserved0 : 2;
    UInt16 SecurityLevel : 1;
    UInt16 Reserved1 : 7;
  } SecurityStatus;
  UInt16 ReservedWord129[31];
  struct {
    UInt16 MaximumCurrentInMA : 12;
    UInt16 CfaPowerMode1Disabled : 1;
    UInt16 CfaPowerMode1Required : 1;
    UInt16 Reserved0 : 1;
    UInt16 Word160Supported : 1;
  } CfaPowerMode1;
  UInt16 ReservedForCfaWord161[7];
  UInt16 NominalFormFactor : 4;
  UInt16 ReservedWord168 : 12;
  struct {
    UInt16 SupportsTrim : 1;
    UInt16 Reserved0 : 15;
  } DataSetManagementFeature;
  UInt16 AdditionalProductID[4];
  UInt16 ReservedForCfaWord174[2];
  UInt16 CurrentMediaSerialNumber[30];
  struct {
    UInt16 Supported : 1;
    UInt16 Reserved0 : 1;
    UInt16 WriteSameSuported : 1;
    UInt16 ErrorRecoveryControlSupported : 1;
    UInt16 FeatureControlSuported : 1;
    UInt16 DataTablesSuported : 1;
    UInt16 Reserved1 : 6;
    UInt16 VendorSpecific : 4;
  } SCTCommandTransport;
  UInt16 ReservedWord207[2];
  struct {
    UInt16 AlignmentOfLogicalWithinPhysical : 14;
    UInt16 Word209Supported : 1;
    UInt16 Reserved0 : 1;
  } BlockAlignment;
  UInt16 WriteReadVerifySectorCountMode3Only[2];
  UInt16 WriteReadVerifySectorCountMode2Only[2];
  struct {
    UInt16 NVCachePowerModeEnabled : 1;
    UInt16 Reserved0 : 3;
    UInt16 NVCacheFeatureSetEnabled : 1;
    UInt16 Reserved1 : 3;
    UInt16 NVCachePowerModeVersion : 4;
    UInt16 NVCacheFeatureSetVersion : 4;
  } NVCacheCapabilities;
  UInt16 NVCacheSizeLSW;
  UInt16 NVCacheSizeMSW;
  UInt16 NominalMediaRotationRate;
  UInt16 ReservedWord218;
  struct {
    UInt8 NVCacheEstimatedTimeToSpinUpInSeconds;
    UInt8 Reserved;
  } NVCacheOptions;
  UInt16 WriteReadVerifySectorCountMode : 8;
  UInt16 ReservedWord220 : 8;
  UInt16 ReservedWord221;
  struct {
    UInt16 MajorVersion : 12;
    UInt16 TransportType : 4;
  } TransportMajorVersion;
  UInt16 TransportMinorVersion;
  UInt16 ReservedWord224[6];
  UInt32  ExtendedNumberOfUserAddressableSectors[2];
  UInt16 MinBlocksPerDownloadMicrocodeMode03;
  UInt16 MaxBlocksPerDownloadMicrocodeMode03;
  UInt16 ReservedWord236[19];
  UInt16 Signature : 8;
  UInt16 CheckSum : 8;
} ATAIdentifyData;

class AHCIController
{
public:
    AHCIController(hbaMem *p);
    virtual ~AHCIController();

    hbaPort *getPort(int i);
    bool read(hbaPort *port, UInt16 *buf, UInt32 lba, UInt16 sectors);

private:
    void probeSATAPorts();
    int checkDriveType(hbaPort *port);
    void rebasePort(hbaPort *port, int portNumber);
    void stopCommand(hbaPort *port);
    void startCommand(hbaPort *port);
    int findCmdSlot(hbaPort *port);
    void swapBytes(UInt8 *buf, UInt32 len);
    void identifyPort(hbaPort *port);

    hbaMem *abar; // AHCI Base Address Register = PCI BAR5
    UInt8 nrPorts; // number of ports implemented on this controller
    UInt8 nrCmdSlots; // number of command slots per port
};

#endif // ATA_H