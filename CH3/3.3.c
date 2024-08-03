/* Function that expands shorthand notation a-z or 0-9
 * Prints Leading or Trailing Dashes
 * Will break if the expansion is larger than 1000 characters*/
#include <ctype.h>
#include <stdio.h>
#define MAXLINE 1000

void expand(char s1[], char s2[]);

int mgetline(char s[], int lim);

int main(int argc, char *argv[]) {
  char s1[MAXLINE], s2[MAXLINE];

  mgetline(s1, MAXLINE);

  expand(s1, s2);

  printf("S1: %s\n", s1);
  printf("S2: %s\n", s2);
}

void expand(char s1[], char s2[]) {
  int a, l, c, i, j;

  j = 0;
  if (s1[0] == '\0') {
    printf("Empty String\n");
    return;
  }

  // Checks in a window of 3 chars
  for (i = 0; s1[i] != '\0' && i < MAXLINE - 4; i++) {
    if (isdigit(s1[i]) && s1[i + 1] == '-' &&
        isdigit(s1[i + 2])) { // Check for digit expansion
      a = s1[i];
      l = s1[i + 2];
      while (a <= l) {
        s2[j++] = a++;
      }
    } else if (islower(s1[i]) && s1[i + 1] == '-' &&
               islower(s1[i + 2])) { // Check for alphabet expansion
      // assume lower for now
      a = s1[i];
      l = s1[i + 2];
      while (a <= l) {
        s2[j++] = a++;
      }
    }
    s2[j] = '\0';
  }
}

int mgetline(char s[], int lim) {
  int c, i;

  for (i = 0; (c = getchar()) != EOF && i < lim - 1; i++) {
    s[i] = c;
  }
  s[i] = '\0';

  return 0;
}
