/* Extend entab and detab to accept the shorthand entab -m + n
 * to mean tab stops every n columns, starting at column m. Choose
 * convenient default behaviour) */
#include <stdio.h>

#define TABSPACE 4 // tabs are 8 spaces

int main(void) {
  int c, col;
  int tabspace = TABSPACE;
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      col = col % tabspace;
      // if (col == 0){      // space to the next tab
      //    col = 8;
      // }
      for (int i = 0; i < tabspace - col; i++) {
        putchar(' ');
      }
      continue;
    }
    col++;
    if (c == '\n') {
      col = 0;
    }
    putchar(c);
  }
}
