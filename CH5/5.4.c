/* Write the function strend(s,t), which returns 1 if the string t occurs
 * at the end of string s, and 0 otherwise */

#include <stdio.h>

#define MAXLINE 1000

int mgetline(char s[], int lim);

int strend(char *s, char *t);

int mystrlen(char *s);

int main(int argc, char *argv[]) {
  char s[MAXLINE], t[MAXLINE];

  mgetline(s, MAXLINE);
  mgetline(t, MAXLINE);
  printf("String s: %s\n", s);
  printf("String t: %s\n", t);

  printf("Returned value: %i\n", strend(s, t));
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

int mystrlen(char *s) {
  int i;
  for (i = 0; (*s++) != '\0'; i++)
    ;
  return i + 1;
};

int strend(char *s, char *t) {
  int length_s, length_t;
  length_s = mystrlen(s);
  length_t = mystrlen(t);

  if (length_s < length_t)
    return 0;

  char *endptr;

  endptr = s + length_s - length_t;

  while (*endptr != '\0') {
    if (*endptr != *t) {
      printf("Not the same ending!\n s = %c\n t = %c\n", *endptr, *t);
      return 0;
    }
    endptr++;
    t++;
  }
  printf("Endings match\n");
  return 1;
}
