// ATA IDE driver
// Zoe Knox 2019

#include <hw/ata.h>

struct ideChannel ideChannels[2];
struct ideDevice ideDevices[4];
UInt8 ideBuffer[2048];

static UInt8 ideIRQ = 0;
static Uint8 atapiPacket[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 