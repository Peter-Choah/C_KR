/* Modify the programs entab and detab to accept
 * a list of tab stops as arguments. Use the default tab aettings
 * if there are no arguments. */

#include <stdio.h>

#define TABSTOP 4

int entab(int blanks);

// Replaces blanks with the minimum number of tabs and blanks
// It reads spaces to the next word before printing blanks and tabs
int main(void) {
  int blanks, c, col, tabcount, blankcount;

  while ((c = getchar()) != EOF) {
    // if new word or line, print remainding blanks and reset blanks to 0
    if (c != ' ' && c != '\t' && c != '\n') {
      if (blanks > 0) { // print blanks and tabs
        tabcount += entab(blanks);
        blankcount += blanks;
        blanks = 0;
      }
      putchar(c);
      col++;
      continue;
    }

    // tally the blank spaces
    // if c = blank, increase count
    if (c == ' ') {
      blanks++;
    }
    // if c = \t, increase by blanks to the next TABSTOP
    else if (c == '\t') {
      // blanks = blanks + TABSTOP - (col % TABSTOP);
      col = col + TABSTOP - (col % TABSTOP) -
            1;              // increase column as well, -1 for offset
    } else if (c == '\n') { // removes trailing spaces as well
      putchar('\n');
      printf("tabs: %d\tblanks: %d\n", tabcount, blankcount - (4 * tabcount));
      col = 0;
      blanks = 0;
      blankcount = 0;
      tabcount = 0;
    } else {
      printf("Unknown character: %c", c);
    }
  }
}

// prints out the spaces and returns number of tabs
int entab(int blanks) {
  int tabcount;
  for (int i = 0; i < (blanks % TABSTOP); i++) { // prints(blanks)
    putchar(' ');
  }
  for (int j = blanks; j > TABSTOP; j = j - 4) {
    tabcount++;
    for (int k = 0; k < TABSTOP; k++) { // prints TABSTOPss
      putchar(' ');
    }
  }
  return tabcount;
}
