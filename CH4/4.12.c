/* Adapt the ideas of printd to write a recursive version of itoa; that is,
 * convert an integer into a string by calling a recursive routine. */

#include <stdio.h>

int itoa(char s[], int num);

int main(int argc, char *argv[]) {

  char s[100];

  itoa(s, 12345);
  printf("String: %s\n", s);
}

int itoa(char s[], int num) {

  static int sign = 0;
  static int p = 0;
  if (num < 0) {
    sign = -1;
  }

  if (num / 10) {
    s[p++] = itoa(s, num / 10);
  } else {
    s[p + 1] = '\0';
    return num + '0';
  }

  return num % 10 + '0';
}
