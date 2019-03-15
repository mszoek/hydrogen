#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Screen I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#define WHITE_ON_BLACK 0x0f

// Text Attributes
#define DEFAULT_TEXT_ATTR 0x07    // grey on black
#define DEFAULT_STATUS_ATTR 0x5f  // white on magenta

// Public kernel API
void clearScreen(const char attr);
void kprintAt(const char *message, int col, int row, char attr);
void kprint(const char *message);
int kprintf(const char* str, ...);
int printChar(char c, int col, int row, char attr);

int getCursorOffset();
int getOffset(int col, int row);
int getOffsetRow(int offset);
int getOffsetCol(int offset);
void setCursorOffset(int offxset);

char defaultTextAttr(char attr);

void printBackspace();

#endif

