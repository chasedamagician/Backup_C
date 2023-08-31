#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define PIXEL_TRUE 1
#define PIXEL_FALSE 0

// Core Function.
void drawBraille(int type) {
  if(type > 255) {
    return;
  }
  setlocale(LC_CTYPE, "");
  wchar_t c = 0x2800 + type;
  wprintf(L"%lc", c);
}

/*
  Pixel Array.
  0x01, 0x08,
  0x02, 0x10,
  0x04, 0x20,
  0x40, 0x80,
*/

int pixelArr[8] = {
  0x01, 0x08,
  0x02, 0x10,
  0x04, 0x20,
  0x40, 0x80
};

typedef int cell[8];

void drawCell(cell cell) {
  int total;
  for(int i = 0; i < 8; i++) {
    if(cell[i] == 1) {
      total += pixelArr[i];
    }
  }
  drawBraille(total);
}

// Main.
int main(void) {
  cell a = {
    0, 1,
    0, 0, 
    1, 1,
    0, 1
  };
  drawCell(a);
return 0;
}
