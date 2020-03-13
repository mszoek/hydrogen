#ifndef H2LOGO_H
#define H2LOGO_H

struct imagetype {
  unsigned int   color;
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[315 * 65 * 4 + 1];
};

extern const struct imagetype gimp_image;

#endif