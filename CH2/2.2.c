#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Testing\n");
  printf("Hello world\n");

  int lim = 1000;
  char s[1000];
  char c;

  for (int i = 0; i < lim - 1; ++i) {
    if ((c = getchar()) == '\n') {
      break;
    }
    if (c == EOF) {
      break;
    }
    s[i] = c;
  }
}
