#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Screen I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#define WHITE_ON_BLACK 0x0f

// Public kernel API
void clearScreen(char attr);
void kprintAt(char *message, int col, int row, char attr);
void kprint(char *message);

int getCursorOffset();
void setCursorOffset(int offxset);
int printChar(char c, int col, int row, char attr);
int getOffset(int col, int row);
int getOffsetRow(int offset);
int getOffsetCol(int offset);

char defaultTextAttr(char attr);

void printBackspace();


#endif

