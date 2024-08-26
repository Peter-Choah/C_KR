/* Rwerite readlines to store lines in an array supplied by main, rather than
 * calling alloc to maintain storage. How much faster is the program?*/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);

int main(void) {
  int nlines;
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    return 0;
  } else
    return 1;
}

#define MAXLEN 1000 /* max length of any input line */
int get_line(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

#define ALLOCSIZE 10000          /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else
    return 0;
}

int get_line(char *s, int limit) {
  char c;

  int i = 0;
  while (i < limit && ((c = getchar()) != '\n') && c != EOF) {
    s[i] = c;
    i++;
  }
  return 0;
}
