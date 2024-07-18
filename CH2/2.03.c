// Function that deletes each character in s1 that matches in s2.
#include <stdio.h>

char *squeeze(char s[], char *t);

int main(int args, char *argv[]) {
  printf("Hello World\n");
  printf("Line 2 \n");
  char s[] = "Hello World";
  char *t = "eo";

  printf("Before: %s\n", s);
  squeeze(s, t);
  printf("After: %s\n", s);
}

char *squeeze(char s[], char *t) {
  int i, j, k;
  int match; // check if character matches in t

  for (i = j = 0; s[i] != '\0'; i++) {
    match = 0;
    for (k = 0; t[k] != '\0'; k++) {
      if (s[i] == t[k]) {
        match = 1;
        break;
      }
    }
    if (match == 0)
      s[j++] = s[i];
  }
  s[j] = '\0';

  return s;
}
