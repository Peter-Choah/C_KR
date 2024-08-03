/* Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string . In particular,
 * itob(n,s,16) formats n as a hexadecimal integer in s.*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define abs(x) ((x) > 0 ? (x) : -(x))

int itob(int n, char s[], int b);
void reverse(char s[]);

int main(void) {
  int number, base;
  char st[MAXLINE], t[MAXLINE], u[MAXLINE];

  number = 42425;
  base = 16;

  itob(number, st, 4);
  itob(number, st, base);
  printf("Number: %d\n", number);
  printf("Alphabet: %s\n", st);

  base = 10;
  itob(number, t, base);
  printf("Number: %d\n", number);
  printf("Alphabet: %s\n", t);

  base = 8;
  itob(number, u, base);
  printf("Number: %d\n", number);
  printf("Alphabet: %s\n", u);
  return 0;
}

int itob(int n, char s[], int b) {
  int i, j, sign;

  i = j = 0;
  sign = n;

  if (b != 10 && b != 8 && b != 16) {
    printf("Not a valid base!\n");
    return 1;
  }

  switch (b) {
  case 10:
    printf("Base 10!\n");
    do {
      s[i++] = abs(n % b) + '0';
    } while ((n /= b) != 0);
    printf("%s\n", s);
    break;
  case 8:
    printf("Base 8!\n");
    do {
      s[i++] = abs(n % b) + '0';
    } while ((n /= b) != 0);
    s[i++] = '0';
    break;
  case 16:
    do {
      j = abs(n % b);
      s[i++] = j > 9 ? j - 10 + 'a' : j + '0';
    } while ((n /= b) != 0);
    s[i++] = 'x';
    s[i++] = '0';

    break;
  }

  if (sign < 0) {
    s[i++] = '-';
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
