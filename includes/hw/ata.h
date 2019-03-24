/*
 * H2 AHCI ATA/ATAPI Driver
 * Copyright (C) 2017-2019 Zoe Knox. All rights reserved.
 */

#ifndef ATA_H
#define ATA_H

#include <hw/types.h>

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

typedef volatile struct
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
    hbaPort ports[1];   // 1 - 32
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

class AHCIController
{
public:
    AHCIController();
    virtual ~AHCIController();

    void probeSATAPort(hbaMem *abar);

private:
    int checkDriveType(hbaPort *port);
    void rebasePort(hbaPort *port, int portNumber);
};

#endif // ATA_H