#include <hw/port_io.h>
#include <drivers/screen.h>
#include <kmem.h>

#define COLOR_ERROR 0x4f

// Private functions
int getCursorOffset();
void setCursorOffset(int offset);
int printChar(char c, int col, int row, char attr);
int getOffset(int col, int row);
int getOffsetRow(int offset);
int getOffsetCol(int offset);

/**********************************************************
 * Public Kernel API Functions                            *
 **********************************************************/

void kprintAt(char *message, int col, int row)
{
  int offset;
  if (col >= 0 && row >= 0)
  {
    offset = getOffset(col, row);
  } else {
    offset = getCursorOffset();
    row = getOffsetRow(offset);
    col = getOffsetCol(offset);
  }

  int i = 0;
  while(message[i] != 0)
  {
    offset = printChar(message[i++], col, row, 0x0f);
    row = getOffsetRow(offset);
    col = getOffsetCol(offset);
  }
}

void printBackspace()
{
  int offset = getCursorOffset() - 2;
  if(offset < 0)
  {
    offset = 0;
  }
  *(char *)(VIDEO_ADDRESS + offset) = ' ';
  setCursorOffset(offset);
}

void kprint(char *message)
{
  kprintAt(message, -1, -1);
}

/**********************************************************
 * Private Kernel API Functions                           *
 **********************************************************/

int printChar(char c, int col, int row, char attr)
{
  unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
  if (!attr) attr = 0x0f;

  // Error: print red 'E' if coords aren't correct.
  if (col >= MAX_COLS || row >= MAX_ROWS)
  {
    vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
    vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = COLOR_ERROR;
    return getOffset(col, row);
  }

  int offset;
   if (col >= 0 && row >= 0) offset = getOffset(col, row);
   else offset = getCursorOffset();

   if (c == '\n') {
       row = getOffsetRow(offset);
       offset = getOffset(0, row+1);
   } else {
       vidmem[offset] = c;
       vidmem[offset+1] = attr;
       offset += 2;
   }

   // Video scrolling
   if (offset >= MAX_ROWS * MAX_COLS * 2)
   {
     int i;
     for (i = 1; i < MAX_ROWS; i++)
     {
       memcpy(getOffset(0, i-1) + (unsigned char*)VIDEO_ADDRESS,
         getOffset(0, i) + (unsigned char*)VIDEO_ADDRESS,
         MAX_COLS * 2);
     }

     // Blank last line
     char *last_line = getOffset(0, MAX_ROWS-1) + (unsigned char*)VIDEO_ADDRESS;
     for (i = 0; i < MAX_COLS * 2; i++)
     {
       last_line[i] = 0;
     }

     offset -= 2 * MAX_COLS;
   }
   setCursorOffset(offset);
   return offset;
}

int getCursorOffset() {
   /* Use the VGA ports to get the current cursor position
    * 1. Ask for high byte of the cursor offset (data 14)
    * 2. Ask for low byte (data 15)
    */
   portByteOut(REG_SCREEN_CTRL, 14);
   int offset = portByteIn(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
   portByteOut(REG_SCREEN_CTRL, 15);
   offset += portByteIn(REG_SCREEN_DATA);
   return offset * 2; /* Position * size of character cell */
}

void setCursorOffset(int offset) {
   /* Similar to getCursorOffset, but instead of reading we write data */
   offset /= 2;
   portByteOut(REG_SCREEN_CTRL, 14);
   portByteOut(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
   portByteOut(REG_SCREEN_CTRL, 15);
   portByteOut(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clearScreen() {
  char *vidmem = (char*)VIDEO_ADDRESS; // Start of video memory
  unsigned int j = 0;

  while (j < MAX_COLS * MAX_ROWS * 2)
  {
    vidmem[j++] = ' ';
    vidmem[j++] = WHITE_ON_BLACK;
  }
  setCursorOffset(0); // no need to calc - it is always zero :)
}


int getOffset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int getOffsetRow(int offset) { return offset / (2 * MAX_COLS); }
int getOffsetCol(int offset) { return (offset - (getOffsetRow(offset)*2*MAX_COLS))/2; }
