#ifndef KVERSION_H
#define KVERSION_H

#include <hw/types.h>

// 4 byte version code (major, minor, service pack, patchlevel)
static UInt32 KERN_VERSION = 0x00020000;

#define KERN_MAJOR ((KERN_VERSION & 0xff000000) >> 24)
#define KERN_MINOR ((KERN_VERSION & 0xff0000) >> 16)
#define KERN_SP ((KERN_VERSION & 0xff00) >> 8)
#define KERN_PATCH (KERN_VERSION & 0xff)

#endif

