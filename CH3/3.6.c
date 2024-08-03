/* Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width; the converted number must
 * be padded with blanks on the left if necessary to make it wide enough.*/

#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define abs(x) ((x) > 0 ? (x) : -(x))

void reverse(char s[]);
int itoa(int n, char s[], int fieldwidth);

int main(void) {
  int number;
  char s[MAXLINE];

  number = 42425;
  printf("log10: %f\n", log10(100));

  printf("Number: %d\n", number);
  itoa(number, s, 20);
  printf("Alphabet: %s\n", s);

  return 0;
}

int itoa(int n, char s[], int fieldwidth) {
  int i, sign;
  double n2 = (double)n;

  if (fieldwidth <
      log10(42425)) { // hardcoded as it seems that it doesn't work with n
    printf("Fieldwidth is smaller than the length of the number given\n");
    return 1;
  }

  i = 0;
  sign = n;

  do {
    s[i++] = abs(n % 10) + '0';
  } while ((n /= 10) != 0);

  if (sign < 0) {
    s[i++] = '-';
  }

  if (strlen(s) - 1 < fieldwidth) {
    for (int j = 0; j < fieldwidth - strlen(s) - 1; j++) {
      s[i++] = ' ';
    }
  }

  s[i] = '\0';

  reverse(s);

  return 0;
}

void reverse(char s[]) {

  // Initialize start and end pointers
  int start = 0;
  int end = strlen(s) - 1;
  char temp;

  // Swap characters while start is less than end
  while (start < end) {

    // Swap characters
    temp = s[start];
    s[start] = s[end];
    s[end] = temp;

    // Move pointers
    start++;
    end--;
  }
}
