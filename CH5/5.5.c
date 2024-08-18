/* Write versions of the library functions strncpy, strncat, and strncmp, which
 * operate on at most the first n characters of their argument strings. For
 * example, strncpy(s,t,n) copies at most n characters of t to s.*/

#include <stdio.h>

#define MAXLINE 1000

int mgetline(char s[], int lim);

int mystrlen(char *s);

void mystrncpy(char *s, char *t, int n);
void mystrncat(char *s, char *t, int n);
int mystrncmp(char *s, char *t, int n);

int main(int argc, char *argv[]) {
  char s[MAXLINE], t[MAXLINE], u[MAXLINE];

  char *ptr_s, *ptr_t;

  mgetline(s, MAXLINE);
  mgetline(t, MAXLINE);
  mgetline(u, MAXLINE);

  printf("strncmp: %i\n", mystrncmp(s, t, 3));
  mystrncat(s, t, 5);
  printf("strncat: %s\n", s);
  mystrncpy(s, u, 4);
  printf("strncpy: %s\n", s);

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

void mystrncpy(char *s, char *t, int n) {
  for (int i = 0; i < n; i++) {
    *s++ = *t++;
  }
}

void mystrncat(char *s, char *t, int n) {
  int i = 0;
  while (*s++ != '\0')
    ;
  s--; // remove nul
  while ((*s++ = *t++) && i++ < n)
    ;
  *s = '\0';
}

int mystrncmp(char *s, char *t, int n) {
  for (int i = 0; i < n; i++) {
    if (*s++ != *t++) {
      return 0;
    }
  }
  return 1;
}
