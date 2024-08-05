/* Write the function strrindex(s,t), which returns the position
 * of the rightmost occurrence of t in s, or -1 if is none.*/

#include <stdio.h>

#define MAX 100

int strrindex(char s[], char t[]);

int main(int argc, char *argv[]) {

  char s[] = "how, cow, donut, throw";
  char t[MAX] = "ab";
  s[0] = 'b';

  printf("Index = %i\n", strrindex(s, t));
}

int strrindex(char s[], char t[]) {

  int i, j, k, index;

  index = -1;

  for (i = j = 0; s[i] != '\0'; i++) {
    if (s[i] == t[j]) {
      for (j = 0, k = i; s[k] == t[j] && t[j] != '\0'; j++, k++)
        ;
      if (t[j] == '\0') {
        index = i;
      }
      j = 0;
    }
  }
  return index;
}
