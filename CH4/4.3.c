
/* Exercises on the Polish Calculator 4.3 to 4.10 */

#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100
#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);
double top(void);
void duplicate(void);
void swaptop(void);
void clear(void);

/* reverse Polish Calculator */
int main(void) {
  int type, op3;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
      /*Note: '+' and '*' are commutative so the order of popping doesn't
       * matter*/
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '%':
      op3 = (int)pop();
      if (op3 != 0.0)
        push((int)pop() % op3);
      else
        printf("error: zero modulo\n");
      break;
    case 't':
      printf("Top: %g\n", top());
      break;
    case 'd':
      duplicate();
      break;
    case 's':
      swaptop();
      break;
    case 'c':
      clear();
      break;
    case '\n':
      printf("\t%.8g\n", top());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack*/

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

/* top: return top of the stack */
double top(void) {
  if (sp > 0)
    return val[sp - 1];
  else
    printf("error: stack empty\n");
  return 0.0;
}

/* duplicate: repeat the top element */
void duplicate(void) {
  if (sp > 0) {
    val[sp] = val[sp - 1];
    printf("Duplicated %g at %i\n", val[sp - 1], sp);
    sp++;
  } else
    printf("error: nothing to duplicate\n");
}

/* swaptop: swap the top 2 elements */
void swaptop(void) {
  if (sp > 1) {
    double a, b, c;

    printf("Swapped from %g %g to ", val[sp - 2], val[sp - 1]);
    c = val[sp - 1];
    val[sp - 1] = val[sp - 2];
    val[sp - 2] = c;

    printf("%g %g\n", val[sp - 2], val[sp - 1]);

  } else {
    printf("error: stack too small, < 2\n");
  }
}

/* clear: clears the stack */
void clear(void) {
  while (sp > 0) {
    val[sp - 1] = 0;
    sp--;
  }
  printf("Calc Stack cleared\n");
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c; /* not a number */
  i = 0;
  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
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
