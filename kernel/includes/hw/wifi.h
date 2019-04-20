/*
 * H2 Wireless Networking Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/types.h>

struct arp4
{
	UInt16 htype;		// Hardware type
	UInt16 ptype;		// Protocol type
	UInt8  hlen;		// Hardware address length (Ethernet = 6)
	UInt8  plen;		// Protocol address length (IPv4 = 4)
	UInt16 opcode;		// ARP operation code
	UInt8  srchw[6];	// Source hardware address - hlen bytes
	UInt8  srcpr[4];    // Source protocol address - plen bytes
	UInt8  dsthw[6];    // Destination hardware address - hlen bytes
	UInt8  dstpr[4];    // Destination protocol address - plen bytes
};

class WirelessController {
public:
	WirelessController();
	~WirelessController();

};
