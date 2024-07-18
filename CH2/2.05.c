// Function setbits(x,p,n,y) that returns x with the n bits that begin at
// position p set to the rightmost n bits of y.

#include <stdio.h>

// Example function to print bits left endian.
void printBits(unsigned int num) {
  for (int bit = 0; bit < (sizeof(unsigned int) * 8); bit++) {
    printf("%i ", num & 0x01);
    num = num >> 1;
  }
  printf("\n");
}

int setbits(int x, int p, int n, int y);
int main(int argc, char *argv[]) {

  int x, p, n, y;

  x = 7;
  p = 2;
  n = 2;
  y = 15;
  printf("%li\n", sizeof(x));
  printf("%i\n", x & y);
  printBits(x);
  printBits(y);
}

int setbits(int x, int p, int n, int y) {
  // get rightmost n bits of y
  for (int bit = 0; bit < sizeof(unsigned int) * 8; bit++) {
    printf("%i", y & 0x01);
  }
}
