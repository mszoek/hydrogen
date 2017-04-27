#ifndef VIDEO_PORTS_H
#define VIDEO_PORTS_H

unsigned char portByteIn (unsigned short port);
void portByteOut (unsigned short port, unsigned char data);
unsigned short portWordIn (unsigned short port);
void portWordOut (unsigned short port, unsigned short data);

#endif
