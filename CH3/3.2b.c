#include <stdio.h>
#define MAXLINE 1000
int mgetline(char line[], int lim);
void revert(char s[], char t[]);

int main(void) {
  char s[MAXLINE], t[MAXLINE];

  mgetline(t, MAXLINE);

  revert(s, t);

  printf("%s\n", t);
  printf("%s\n", s);

  return 0;
}

void revert(char s[], char t[]) {
  int i, j;

  i = j = 0;

  while (t[i] != '\0') {
    if (t[i] == '\\') {
      i++;
      switch (t[i]) {
      case 't':
        s[j] = '\t';
        break;
      case 'n':
        s[j] = '\n';
        break;
      default:
        break;
      }
    } else {
      s[j] = t[i];
    }
    i++;
    j++;
  }
  s[j] = '\0';
}

int mgetline(char s[], int lim) {
  int i, c;

  i = 0;
  while (i < lim - 1 && (c = getchar()) != EOF) {
    s[i] = c;
    i++;
  }

  s[i] = '\0';

  return 0;
}
