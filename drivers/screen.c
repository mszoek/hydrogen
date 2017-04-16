#include "screen.h"
#include "video_ports.h"


// Private functions
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

/**********************************************************
 * Public Kernel API Functions                            *
 **********************************************************/

void kprint_at(char *message, int col, int row)
{
  int offset;
  if (col >= 0 && row >= 0)
  {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  int i = 0;
  while(message[i] != 0)
  {
    offset = print_char(message[i++], col, row, 0x0f);
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void kprint(char *message)
{
  kprint_at(message, -1, -1);
}

/**********************************************************
 * Private Kernel API Functions                           *
 **********************************************************/

int print_char(char c, int col, int row, char attr)
{
  unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
  if (!attr) attr = 0x0f;

  // Error: print red 'E' if coords aren't correct.
  if (col >= MAX_COLS || row >= MAX_ROWS)
  {
    vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
    vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = 0x04;
    return get_offset(col, row);
  }

  int offset;
   if (col >= 0 && row >= 0) offset = get_offset(col, row);
   else offset = get_cursor_offset();

   if (c == '\n') {
       row = get_offset_row(offset);
       offset = get_offset(0, row+1);
   } else {
       vidmem[offset] = c;
       vidmem[offset+1] = attr;
       offset += 2;
   }
   set_cursor_offset(offset);
   return offset;
}

int get_cursor_offset() {
   /* Use the VGA ports to get the current cursor position
    * 1. Ask for high byte of the cursor offset (data 14)
    * 2. Ask for low byte (data 15)
    */
   port_byte_out(REG_SCREEN_CTRL, 14);
   int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
   port_byte_out(REG_SCREEN_CTRL, 15);
   offset += port_byte_in(REG_SCREEN_DATA);
   return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
   /* Similar to get_cursor_offset, but instead of reading we write data */
   offset /= 2;
   port_byte_out(REG_SCREEN_CTRL, 14);
   port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
   port_byte_out(REG_SCREEN_CTRL, 15);
   port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
  char *vidmem = (char*)VIDEO_ADDRESS; // Start of video memory
  unsigned int j = 0;

  while (j < MAX_COLS * MAX_ROWS * 2)
  {
    vidmem[j++] = ' ';
    vidmem[j++] = WHITE_ON_BLACK;
  }
  set_cursor_offset(0); // no need to calc - it is always zero :)
}


int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
