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

While the fall-through may seem useful, it is pronte to disintegration in future modification or if it is a dependent upon.



