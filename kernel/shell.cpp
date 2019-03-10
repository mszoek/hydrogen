#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <kmem.h>
#include <kstring.h>
#include <hw/types.h>
#include <shell.h>

// map scan codes 0x00 to 0x58 into en_US layout
const char scanCodesToASCII[] =
{
    -1, 0x1B, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x08,
    0x09, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x0D,
    -1, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    -1, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', -1, '*',
    -1, ' ', -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* f1 to f10 keys */
    -1, -1, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0',
    '.', -1, -1, -1, -1, -1
};

char *PROMPT = "H2> ";
char shellBuffer[1024];
unsigned int shellBufferPos = 0;

void shellStart()
{
  memset(shellBuffer, 0, sizeof(shellBuffer));
  shellBufferPos = 0;
  kprint(PROMPT);
}

void shellExecCommand()
{
  if(strlen(shellBuffer) < 1) return;

  if(strcmp(shellBuffer, "exit") == 0)
  {
    kprint("kk, kthxbye!\n");
    asm("cli");
    asm("hlt");
  }
  if(strcmp(shellBuffer, "hello") == 0)
  {
    kprint("'ello gorgeous!\n");
    return;
  }

  kprintAt("Invalid command\n", -1, -1, 0x0c);
}

void shellCheckInput()
{
  char code;
  int keyUp = 0;
  char buf[1024];
  int length = getKeyboardBuffer(buf, 1023);

  for(int i = 0; i < length; ++i)
  {
    char code = buf[i];
    if(code & 0x80)
    {
      keyUp = 1;
      code &= 0x7F;
    }

    if(keyUp)
    {
      if(code == 0x1C)
      {
        kprint("\n");
        shellBuffer[shellBufferPos++] = 0;
        shellExecCommand();
        shellBufferPos = 0;
        shellBuffer[0] = 0;
        kprint(PROMPT);
        return;
      }
      if(code == 0x0E)
      {
        if(shellBufferPos > 0)
        {
          shellBuffer[--shellBufferPos] = 0;
          printBackspace();
        }
        return;
      }

      if(shellBufferPos >= 1023)
      {
        return;
        // FIXME: we should beep here
      }

      code = scanCodesToASCII[code];
      shellBuffer[shellBufferPos++] = code;
      char key[2];
      key[0]=code;
      key[1]=0;
      kprint(key);
    }
  }
}
