// Function that returns first location where characters in s2 is found in s1

#include <stdio.h>
#include <string.h>

int any(char s[], char *t);

int main(int args, char *argv[]) {
  printf("Hello World\n");
  printf("Line 2 \n");
  char s[] = "Hello World";
  char *t = "or";

  printf("%i\n", any(s, t));
  // printf("%s\n", strpbrk(s, t)); // returns a pointer, pretty cool?
}

int any(char s[], char *t) {
  int i, j;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = 0; t[j] != '\0'; j++) {
      if (s[i] == t[j])
        return i;
    }
  }
  return -1;
}
