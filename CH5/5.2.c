/* Write getfloat, the floating-point analog of getint. What type does getfloat
 * return as its function value? */

#include <ctype.h>
#include <math.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

/* getfloat: get next float from input into *pn */
int getfloat(double *pn) {
  int c, sign;

  while (isspace(c = getch())) /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c); /* it's not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (*pn = 0.0; isdigit(c); c = getch())
    *pn = 10.0 * *pn + (c - '0');
  //// After the dot
  if (c == '.') {
    c = getch();
    for (int dp = 1.0; isdigit(c); c = getch(), dp++)
      *pn = *pn + ((double)(c - '0') / pow(10.0, dp));
  }

  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
