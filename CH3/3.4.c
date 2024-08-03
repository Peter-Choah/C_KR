/* In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^(wordsize-1)). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs.*/

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

void reverse(char s[]);
void itoa(int n, char s[]);
int mgetline(char s[], int lim);

int main(void) {
  int number;
  char s[MAXLINE];

  number = -2147483648;

  printf("Number: %d\n", number);
  itoa(number, s);
  printf("Alphabet: %s\n", s);

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

/* Multiplying the largest negative number by -1 will cause it to overflow
 * To counter that, we just store it as a number, then process the number using
 * an absolute value later, we just check if its negative and add a negative
 * sign*/
void itoa(int n, char s[]) {

  int i, sign;

  sign = n;
  i = 0;
  do { /* generate digits in reverse order */
    s[i++] =
        ((n % 10) > 0 ? (n % 10) : -(n % 10)) + '0'; /*get next absolute digit*/
  } while ((n /= 10) != 0); // change to != rather than >
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';

  reverse(s);
}

int mgetline(char s[], int lim) {
  int i, c;
  i = 0;
  while ((c = getchar()) != EOF && i < lim - 1) {
    s[i++] = c;
  }
  s[i] = '\0';
  return 0;
}
