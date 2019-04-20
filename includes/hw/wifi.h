/*
 * H2 Wireless Networking Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

class WirelessController {

struct arp
{
	UInt16 htype;		// Hardware type
	UInt16 ptype;		// Protocol type
	UInt8  hlen;		// Hardware address length (Ethernet = 6)
	UInt8  plen;		// Protocol address length (IPv4 = 4)
	UInt16 opcode;		// ARP operation code
	UInt8  srchw[hlen];	// Source hardware address - hlen bytes
	UInt8  srcpr[plen]; // Source protocol address - plen bytes
	UInt8  dsthw[hlen]; // Destination hardware address - hlen bytes
	UInt8  dstpr[plen]; // Destination protocol address - plen bytes
}

public:
	WirelessController();
	~WirelessController();

};