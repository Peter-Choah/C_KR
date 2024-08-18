/* Write a pointer version of the function strcat that we showed in Chapter 2:
 * strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>

#define MAXLINE 1000

int mgetline(char s[], int lim);

void mystrcat(char *s, char *t);

int main(int argc, char *argv[]) {
  char s[MAXLINE], t[MAXLINE];

  int length = 0;
  length += mgetline(s, MAXLINE);
  length += mgetline(t, MAXLINE);
  printf("String s: %s\n", s);
  printf("String t: %s\n", t);

  if (length < 1000) {
    length--;
    mystrcat(s, t);
  } else {
    printf("Concatenated string is too long\n");
    return 1;
  }
  printf("String s2: %s\n", s);
  printf("Length %i\n", length);

  return 0;
}

int mgetline(char s[], int lim) {
  int i;
  char c;

  i = 0;
  while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;

  if (s[i] == '\n') {
    s[i++] = c;
  }
  s[i] = '\0';

  return i + 1;
}

void mystrcat(char *s, char *t) {
  while (*s++ != '\0')
    ;
  s--; // remove nul
  while (*s++ = *t++)
    ;
}
