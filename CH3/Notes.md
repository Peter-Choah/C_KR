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

