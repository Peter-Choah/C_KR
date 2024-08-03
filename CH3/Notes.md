# Control Flow

## 3.1 Statements and Blocks

Statements are lines that has a semicolon.

Blocks / compound statements are groups of statements enclosed by { and }.

## 3.2 If-Else

Don't get caught with an else statement for an if statement.

if (...) 
  for () 
    if() {}
else;  // this will be for the if statement within the for statement

## 3.3 Else-If

Nothing much to note.

On the exercise about binary search, it could be more reusable if we returned the index rather than the value.

Also, finding the mid is better by using
  mid = low + (high - low) / 2;
rather than
  mid = (low+high) / 2;
to avoid int overflow.

## 3.4 Switch

Syntax:
switch (expression) {
  case const-expr: statements
  case const-expr: statements
  default: statements
}

Execution falls through all cases. Please use breaks or return to escape switch statements. Even for the default statement as a safeguard for additional cases in the future.

While the fall-through may seem useful, it is prone to disintegration in future modification or if it is a dependent upon.

## 3.5 While and For

  for (expr_1; exper_2; expr_3)
    statement

is equivalent to

  expr_1;
  while (expr_2) {
    statement
    expr3;
  }

Generally, the three expressions are most commonly:
-expr_1: assignments or function calls 
-expr_2: relational expression 
-expr_3: assignments or function calls

Any of the three expressions can be omitted, but the semicolons must remain in the for loop.

If expr_2 is omitted, it will be taken as permanently true.

  for (;;) {
    ...
  }

is an infinite loop, that presumably is broken by break or return statements.

Whether to use while or for is mostly a matter of personal preference.

  while ((c=getchar()) == ' ' || c == '\n' || c == '\t'); // skips white space characters

There is no initialization or re-initialization, so the while is most natural.

For is preferable when there is a simple initialization and increment, since it keeps loop control statements close together and visible at the top of the loop.

### Comma Operators
Sometimes comma operators can be used in for statements as well which guarantees left to right evaluation.

/* reverse string s in place */
void reverse(char s[])
{
  int c, i, j;

  for (i = 0, j = strlen(s)-1; i < j; i++, j--) // here two indices are used
    c = s[i];
    s[i] = s[j];
    s[j] = c;
}

Commas that separate function arguments, variables in declarations, etc, are not comma operators and do not guarantee left to right evaluation.

## 3.6 Do While

Do while loops differs from the others by testing *after* making each pass through the loop body.
Thus, it is always executed at least once.

Syntax:
  do
    statement
  while (expression);
See exercise 3.3c for an example of a do while loop.
  ^ necessary as it needs to print something eventhough it could be a 0 value.

## 3.7 Break and Continue

Break causes the innermost enclosing loop or switch to be exited immediately.

Continue causes the next iteration of the enclosing for, while, or do loop to begin.
In while and do, this means that the test part is executed immediately.
In for, control passes to the increment step.
Doesn't affect switch.

## Goto and Labels

Goto can break out of two or more loops at once.

for ( ... )
  for ( ... ) {
      ...
      if (disaster)
        goto error;
  }
...

error:
  clean up the mess

Kinda handy if the error-handling code is non-trivial and if errors can occur in several places.

A label has the same form as a variable name, and is followed by a colon.
It can be attached to any statement in the same function as the goto. The scope ofa label is the entire function.

Another example of determining whether two arrays a and b have an element in common.

    for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
        if (a[i] == b[j])
          goto found;
    /* didn't find any common element */
    ...
  found:
    /* got one: a[i] == b[j] */
    ...

Code involving goto can always be rewritten without one maybe at the cost of some repeated tests or an extra variable.

  found = 0;
  for (i = 0; i < n && !found; i++)
    for (j = 0; j < m && !found j++)
      if (a[i] == b[j])
        found = 1;
  if (found)
    /* got one: a[i-1] == b[j-1] */
    ...
  else
    /* didn't find any common element */
    ...

Don't use goto if possible. It makes you look around the entire codebase.
