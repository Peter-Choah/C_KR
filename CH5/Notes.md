# Pointers and Arrays

A pointer is a variable that contains the address of a variable. Pointers are much used in C, partly because they are sometimes the only way to express a computation, and partly because they usually lead to a more compact and efficient code. Pointers and arrays are closely related.

Pointers can be really bad when used carelessly, like pointing to somewhere unexpected. 

## 5.1 Pointers and Addresses

A typical machine has an array of consecutively numbered or addressed memory cells that may be manipulated individually or in contiguous groups. Any byte can be a char, a pair of one-byte cells can be treated as a short integer, and four adjacent bytes form a long. A pointer is a group of cells that can hold an address. 
If c is a char and p is a pointer that points to it:

  p = &c

The unary operator & gives the address of an object. Thus, the statement above assigns the address of c to the variable p, and p is said to "point to" c. The & operator only applies to objects in memory: variables and array elements. It cannot be applied to expressions, constants, or register variables.

The unary operator * is the indirection or dereferencing operator; when applied to a pointer, it accesses the object the pointer points to. Suppose that x and y are integers and ip is a pointer to int. 
E.g
```
  int x = 1, y = 2, z[10];
  int *ip;      /* ip is a pointer to int */
  
  ip = &x;      /* ip now points to x */
  y = *ip;      /* y is now 1 */
  *ip = 0;      /* x is now 0 */
  ip = &z[0];   /* ip now points to z[0] */
 ```

The declaration 
  int *ip;
is intended as a mnemonic; it says that the expression *ip is an int. Similarly for function declarations:
```
  double *dp, atof(char *);
```
says that in an expression *dp and atof(s) have values of type double, and that the argument of atof is a pointer to char.

Note that the implication that a pointer is constrained to point to a particular kind of object unless if its a pointer to void which is used to hold any type of pointer (but cannot be dereferenced itself).

If ip points to the integer x, then *ip can occur in any context where x could, so
```
*ip = *ip + 10;
```
is equal to
```
  x = x + 10
```
Unary operators * and & bind more tightly than arithmetic operators.
```
  y = *ip + 1
```
takes whatever ip points at, adds 1, and assigns the result to y, while
```
  *ip += 1
```
increments what ip points to, as do
```
  ++*ip
```
and
```
  (*ip)++
```
Parentheses above are necessary or else the expression would increment ip instead of what it points to.

Since pointers are variables, they can be used without dereferencing.
```
  iq = ip // iq is another pointer to int
```
The line above copies contents of ip into iq, thus making iq point to whatever ip pointed to.

## 5.2 Pointers and Function Arguments

Since C passes arguments to functions by value, there is no direct way for the called function to alter a variable in the calling function. For instance, a sorting routine might exchange two out-of-order elements with a function called swap. 
```
void swap(int x, int y)
{
  int temp;
  temp = x;
  x = y;
  y = temp;
}
```
Simply calling this function swap(a,b); is not enough as it cannot affect the arguments a and b in the routine that called it. It only swaps copies of a and b.

A solution to this is to pass pointers to the values to be changed:
```
  swap(&a, &b);
```
Since the operator & produces the address of a variable, &a is a pointer to a. In swap itself, the parameters are declared to be pointers, and the operands are accessed indirectly through them.
```
void swap(int *px, int *py) /* interchange between *px and *py */
{
  int temp;

  temp = *px;
  *px = *py;
  *py = temp;
}
```
Pointer arguments enable a function to access and change objects in the function that called it. 
Consider 'gentint' that performs free-format input conversion by breaking a stream of characters into integer values, one integer per call. getint has to return the value it found and also signal end of file when there is no more input. These values have to be passed back by separate paths, for no matter what value is used for EOF, that could also be the value of an input integer.

One solution is to have getint return the end of file status as its function value, while using a pointer argument to store the converted integer back in the calling function. Used in scanf as well.
The following loop fills an array with integers by calls to getint:
```
int n, array[SIZE], getint(int *);

for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
  ;
```
Each call sets array[n] to the next integer found in the input and increments n. Notice that it is essential to pass the address of array[n] to getint. Otherwise there is no way for getint to communicate the converted integer back to the caller.

This version of getint returns EOF for end of file, zero if the next input is not a number, and a positive value if the input contains a valid number.
  *** See getint.c
Throughout getint, *pn is used as an ordinary int variable. 

### 5.3 Pointers and Arrays

In C, there is a strong relationship between pointers and arrays. Any operation that can be achieved by array subscripting can also be done with pointers. The pointer will in general be faster, but harder to understand for newbs.

The declaration
```
  int a[10];
```
defines an array a of size 10, or a block of 10 consecutive objects named a[0 - 9 \].

If pa is a pointer to an integer declared as
```
  int *pa;
```
then the assignment
```
  pa = &a[0];
```
sets pa to point to element zero of a; that is, pa contains the address of a[0\].
Now the assignment
```
  x = *pa;
```
will copy the contents of a[0\] into x.

If pa points to a particular element of an array, then by definition pa+1 points to the next element, pa+i points i elements after pa, and pa-i points i elements before.
Pointer arithmetic with arrays are true regardless of the type or size of the variables in the array. The meaning of "adding 1 to a pointer," and by extension, all pointer arithmetic, is that pa+1 points to the next object, and pa+i points to the i-th object beyond pa.

The name of an array is a synonym for the location of the initial element.
```
  pa = &a[0]
  pa = a // equivalent
```
Reference to a[i\] can also be written as *(a+i) or that &a[i\] and a+i are identical.
OTOH, if pa is a pointer, expressions may use it with a subscript; pa[i\] is identical to *(pa+i).
In short, an array-and-index expression is equivalent to one written as a pointer and offset.

There is one difference between an array name and a pointer that must be kept in mind.
A pointer is a variable, so pa=a and pa++ are legal. But an array name is not a variable; constructions like a=pa and a++ are illegal.

When an array name is passed to a function, what is passed is the location of the initial element. Within the called function, this argument is a local variable, and so an array name parameter is a pointer, that is, a variable containing an address. We can use this to write another version of strlen.
```
/*strlen: return the length of string s */
int strlen(char *s)
{
  int n;
  
  for (n = 0; *s != '\0'; s++)
    n++;
  return n;
}
```
Since s is a pointer, incrementing it is perfectly legal; s++ has no effect on the character string in the function that called strlen, but merely increments strlen's private copy of the pointer. Calls below all work.
```
strlen("hello, world"); /* string constant */
strlen(array);          /* char array[100]; */
strlen(ptr);            /* char *ptr; */
```
As formal parameters in a function definition,
```
  char s[];
  char *s;
```
are both equivalent; the latter is preferred as it says more explicitly that the parameter is a pointer. When an array name is passed to a function, the function can at its convenience believe that it has been handed either an array or a pointer, and manipulate it accordingly. It can even use both notations if it seems appropriate and clear.

It is possible to pass part of an array to a function, by passing a pointer to the beginning of the subarray.
```
  f(&a[2])
  f(a+2)
```
Within f, the parameter declaration can read
```
  f(int arr[]) { ... }
  f(int *arr) { ... }
```

As far as f is concerned, the fact that the parameter refers to part of a larger array is of no consequence.
If one is sure that the elements exist, it is also possible to index backwards in an array; p[-1\], etc, only if they are legal (within the array bounds).

## 5.4 Address Arithmetic

Let p be a pointer to some element of an array. Then p++, p+=i is similar to doing array[p++/], array[p+i/].

An example with a simple storage allocator. alloc(n), returns a pointer p to n-consecutive character positions, which can be used by the caller of alloc for storing characters. afree(p), releases the storage so it can be re-used later. These routines are "rudimentary" because the calls to afree must be made in opposite order to the calls made on alloc. That is, the storage managed by alloc and afree is a stack, or last-in, first-out list. The standard library provides analogous functions called malloc and free that have no such restrictions. 

The easiest implementation is to have alloc hand out pieces of a large character array, allocbuf. This array is private to alloc and afree. Since they deal in pointers, not array indices, no other routine needs to know the name of the array, which can be declared static in the source file containing alloc and afree, and is thus invisible outside it. The array may not even have a name and be instead be obtained by calling malloc or by asking the operating system for a pointer to some unnamed block of storage.

The other information needed is how much of allocbuf has been used. We can use a pointer, called allocp, that points to the next free element. When alloc is asked for n characters, it checks to see if there is enough room left in allocbuf. If so, it returns the current value of allocp and increments it to the next free area. If there is no room, alloc returns zero or something appropriate. afree(p) just sets allocp to p if p is inside allocbuf.

  *** See simple_alloc.c

In general, a pointer can be initialized just as any other variable can, though normally the only meaningful values are 0 or an expression involving the addresses of previously defined data of appropriate type.
```
  static char *allocp = allocbuf;
```
The statement defines allocp to be a character pointer and initializes it to point to the beginning of allocbuf, which is the next free position when the program starts.
It could also be written this way since the array name is the address of the 0th element.
```
  static char *allocp = &allocbuf[0];
```

0 is never a valid address for data, so a return value of 0 can be used to signal an abnormal event.

Pointers and integers are not interchangeable. Zero is the only exception: the constant zero may be assigned to a pointer, and a pointer may be compared with the constant zero. The symbolic constant NULL is often used in place of zero, as a mnemonic to indicate more clearly that this is a special value for a pointer. NULL is defined in <stdio.h>.

Tests like
```
  if (allocbuf + ALLOCSIZE - allocp >= n )

  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
```
These tests show that pointers can be compared under certain circumstances. If p and q point to members of the same array, then relations like ==, !=, <, >=, etc., work properly. 
Let p < q, (both pointers to the array)
It is true if p points to an earlier member of the array than q does. Any pointer can be meaningfully compared for equality or inequality with zero. But the behaviour is undefined for arithmetic or comparisons with pointers that do not point to members of the same array. (One exceptions being: the address of the first element past the end of an array can be used in pointer arithmetic.)

Another point about pointers is that a pointer and an integer may be added or subtracted. It is true regardless of the kind of object p points to; the added integer is scaled to the size of the object p points to. If an int is four bytes, the int will be scaled by four.

Pointer arithmetic is consistent: if we had been dealing with floats, which occupy more storage than chars, and if p were a pointer to float, p++ would advance to the next float. Thus, we can write another version of alloc that maintains floats instead of chars by simply changing char to float throughout alloc and afree. All pointer manipulations automatically take into account the size of object pointed to.

The valid pointer operations are assignment of pointers of the same type, adding or subtracting a pointer and an integer, subtracting or comparing two pointers to members of the same array, and assigning or comparing to zero. 
Any other pointer arithmetic is illegal: adding 2 pointers, multiply, divide, shift, mask, or add float or double, and (except for void *), assign a pointer of one type to a pointer of another type without a cast.

## 5.5 Character Pointers and Functions

A string constant, "I am a string" is an array of characters. In the internal representation, the array is terminated with NUL. The length in storage is 1 more than the num of characters.
```
  printf("hello, world\n");
```
When a character string like this appears, access to it is through a character pointer; printf receives a pointer to the beginning of the character array.
```
  char *pmessage;
  pmessage = "now is the time";
```
This code block assigns to pmessage a pointer to the character array. This is not a string copy; only pointers are involved. C does not provide any operators for processing an entire string of characters as a unit.
```
  char amessage[] = "now is the time"; /* an array */
  char *pmessage = "now is the time"; /* a pointer */
```
Take note that there are differences between the two. amessage is an array, just big enough to hold the sequence of characters and '\0' that initializes it. Individual characters within the array may be changed but amessage will always refer to the same storage.
pmessage is a pointer, initialized to point to a string constant; the pointer may subsequently be modified to point elsewhere, but the result is undefined if you try to modify the string contents.

strcpy(s,t), is a function from the standard library which copies string t to string s. To copy the characters, we need a loop.
```
/* strcpy: array subscript version */
void strcpy(char *s, char *t)
{
  int i;

  i = 0;
  while ((s[i] = t[i]) != '\0')
    i++;
}

/* strcpy: pointer version 1 */
void strcpy(char *s, char *t)
{
  while ((*s = *t) != '\0') {
    s++;
    t++;
  }
}
```
Because arguments are passed by value, strcpy can use the parameters s and t in any way it pleases.
```
/* strcpy: pointer version 2 */
void strcpy(char *s, char *t)
{
  while ((*s++ = *t++) != '\0')
    ;
}
```
This moves the increment of s and t into the test part of the loop. The value of *t++ is the character that t pointed to before t was incremented; the postfix ++ doesn't change t until after this character has been fetched. In the same way, the character is stored into the old s position before s is incremented. This value is also the value that is compared against '\0' to control the loop. The net effect is that characters are copied from t to s, up to and including the terminating '\0'.

For the final abbreviation, observe that a comparison against '\0' is redundant since the question is merely whether the expression is 0.
```
/* strcpy: pointer version 3 */
void strcpy(char *s, char *t)
{
  while (*s++ = *t++)
    ;
}
```
This is cryptic, but the notational convenience is considerable, and is quite common in C programs.
To note, the strcpy in <string.h> returns the target string as its function value.

strcmp(s,t), which compares the character strings s and t, and returns negative, zero or positive if s is lexicographically less than, equal to, or greater than t. The value is obtained by subtracting the characters at the first position where s and t disagree.
```
/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *s, char *t)
{
  int i;

  for (i = 0; s[i] == t[i]; i++)
    if (s[i] == '\0')
      return 0;
  return s[i] - t[i];
}

/* strcmp: pointer version */
int strcmp(char *s, char *t)
{
  for ( ; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}
```
Common idioms using prefix or postfix operators:
```
  *p++ = val;   /* push val onto stack */
  val = *--p;   /* pop top of stack into val */
```

## 5.6 Pointer Arrays; Pointers to Pointers

Pointers are variables themselves, and they can be stored in arrays just as other variables can.

Imagine sorting a set of text lines into alphabetic order, or the UNIX program sort. For integers, we can use simpler algorithms like Shell sort or quicksort, but now we have to deal with lines of text, which are of different lengths. Also, they can't be compared or moved in a single operation like with integers. We need a data representation that will cope efficiently and conveniently with variable length text lines.

Using an array of pointers, if the lines to be sorted are stored end-to-end in one long character array, then we can access each line with a pointer to its first character. The pointers themselves can be stored in an array. Two lines can be compared by passing their pointers to strcmp. When two out-of-order lines have to be exchanged, the pointers in the pointer array are exchanged, not the text lines themselves.

This eliminates the twin problems of complicated storage management and high overhead that would go with moving the lines themselves.
The main program does these three things in order: read all the lines of input, sort them, print them in order.

The input routine has to collect and save the characters of each line, and build an array of pointers to the lines. It will also have to count the number of input lines, since that information is needed for sorting and printing. Since the input function can only cope with a finite number of input lines, it can return some illegal line count like -1 if too much input is presented.

The output routine only has to print the lines in order in which they appear in the array of pointers.

 *** See sort_lines.c

char *lineptr[MAXLINES\] is the main thing. lineptr is an array of MAXLINES elements, each element of which is a pointer to a char. To be clear, lineptr[i\] is a **character pointer**, and *lineptr[i\] is the **character it points to**, which is the first character of the i-th saved text line.

Since lineptr is itself the name of an array, it can be treated as a pointer in the same manner as in our examples, and writelines can be written instead as
```
/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}
```
For sorting, the quicksort from CH4 needs minor changes: the declarations have to be modified and the comparison operation must be done calling strcmp. The algorithm remains the same.

## 5.7 Multi-dimensional Arrays

It's more popular to use arrays of pointers than rectangular multi-dimensional arrays. 

Here's two functions: day_of_year to convert month and day into day of the year, and month_day converting the day of year into month and day. Since the latter function computes two values, the month and day arguments will be pointers.
```
  month_day(1988, 60, &m, &d) // sets m to 2 and d to 29
```
These functions both need the same information, a table of the number of days in each month. Since the number of days per month differs for leap years and non-leap years, it's easier to separate them into two rows of a two-dimensional array than to keep track of what happens to February during computation, shown below.
```
static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;
  
  leap = year%4 == 0 && year %100 != 0 || year$400 == 0;
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}
```
Interesting use of true and false here as the subscript for the leap years of the array daytab. daytab is also external so both functions can use it. Char is used to illustrate a legitimate use of char for storing small non-character integers.

In reality, the 2-dimensional array of daytab is just a one-dimensional array with arrays as its elements. The subscripts are written as:
```
  daytab[i][j] /* [row][col] */
  daytab[i,j] /* WRONG */
```
An array is initialized by a list of initializers in braces; each row of a two-dimensional array is initialized by a corresponding sub-list. The array daytab started with 0 so the month numbers can run from 1 to 12 instead of 0 to 11. This is done since space isn't much of a big deal here.

If a two-dimensional array is passed to a function, the parameter declaration in the function must include the number of columnsl the number of rows is irrelevant, since what is passed is, as before, a pointer to an array of rows, where each row is an array of 13 ints. In this particular case, it is a pointer to objects that are arrays of 13 ints. Thus if the array daytab is to be passed to a function f, the declaration of f would be
```
  f(int daytab[2][13]) {...}
  // or
  f(int daytab[][13]) {...}
  // or since the number of rows is irrelevant,
  f(int (*daytab[13])) {...}
```
The last function declaration says that the parameter is a pointer to an array of 13 integers. The parentheses are necessary since brackets[] have higher precedence than *. Otherwise it is an array of 13 pointers to integers. More generally, only the first dimension (subscript) of an array is free; all others have to be specified.

## 5.8 Initialization of Pointer Arrays

Consider a function month_name(n) which returns a pointer to a character string containing the name of the n-th month. month_name contains a private static array of character strings, and returns a pointer to the proper one when called. This sections shows how that array of names is initialized.
The syntax is similar to previous initializations:
```
/* month_name: return name of n-th month */
char *month_name(int n)
{
  static char *name[] = {
    "Illegal month",
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
  };
  
  return (n < 1 || n > 12) ? name[0] : name[n];
}
```

The declaration of name, which is an array of character pointers, is the same as lineptr in the sorting example. The initializer is a list of character strings; each is assigned to the corresponding position in the array. The characters of the i-th string are placed somewhere, and a pointer to them is stored in name[i\]. Since the size of the array name is not specified, the compiler counts the initializers and fills in the correct number.

## 5.9 Pointers vs Multi-dimensional Arrays

Given the definitions
```
  int a[10][20];
  int *b[10];
```
then a[3\][4\] and b[3\][4\] are both syntactically legal references to a single int. But a is a true-dimensional array: 200 int-sized locations have been set aside, and the conventional rectangular subscript calculation 20 x row+col is used to find the element a[row\][col\then a[3\][4\] and b[3\][4\]. b however, the definition only allocates 10 pointers and does not initialize them; initialization must be done explicitly, either statically or with code. Assuming that each element of b does point to a twenty-element array, then there will be 200 ints set aside, plus ten cells for the pointers. The important advantage of the pointer array is that the rows of the array may be of different lengths. That is, each element of b need not point to a twenty-element vector; some may point to two elements, some to fifty, and some to none at all.

Although integers are used above, the most frequent use of arrays of pointers is to store character strings of diverse lengths, as in the function month_name. 

## 5.10 Command-line Arguments

When main is called, it is called with two arguments. The first (conventionally called argc, for argument count) is the number of command line arguments the program was invoked with; the second (argv, for argument vector) is a **pointer** to an array of character strings that contain the arguments, one per string. We customarily use multiple levels of pointers to manipulate these character strings.

Take the command-line call -> echo hello, world

By convention, argv[0\] is the name by which the program was invoked, so argc is at least 1. If argc is 1, there are no command-line arguments after the program name. In the example above, argc is 3, argv[0\], argv[1\], and argv[2\] are "echo", "hello,", and "world" respectively. The first optional argument is argv[1\] and the last is argv[argc-1\]; additionally, the standard requires that argv[argc\] be a null pointer.

The first version of echo treats argv as an array of character pointers:
```
#include <stdio.h>

/* echo command-line arguments; 1st version */
main(int argc, char *argv[])
{
  int i;

  for (i = 1; i < argc; i++)
    printf("%s%s", argv[i], (i < argc-1) ? " " : "");
  printf("\n");
  return 0;
}
```
Since argv is a pointer to an array of pointers, we can manipulate the pointer rather than index the array. This next variation is based on incrementing argv, which is a pointer to char, while argc is counted down:
```
#include <stdio.h>

/* echo command-line arguments; 2nd version */
main(int argc, char *argv[])
{
  while (--argc > 0)
    printf("%s%s", *++argv, (argc > 1) ? " ", "");
  printf("\n");
  return 0;
}
```
Since argv is a pointer to the beginning of the array of argument strings, incrementing it by 1 makes it point at the original argv[1\] instead of argv[0\]. Each successive increment moves it along to the next argument; *argv is then the pointer to that argument. At the same time, argc is decremented, and when it becomes 0, there are no arguments left to print.

Alternatively, we could write the printf statement as
```
  printf((argc > 1) ? "%s " : "%s", *++argv);
```
Showing that the format argument of printf can be an expression too.

For a 2nd example, here's some enhancements to the pattern-finding program from Section 4.1. We wired the search pattern deep into the program, an obviously unsatisfactory arrangement. Following the lead of the UNIX program grep, let us change the program so the pattern to be matched is specified by the first argument on the command line.
```
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);

/* find: print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
  char line[MAXLINE];
  int found = 0;

  if (argc != 2)
    printf("Usage: find pattern\n");
  else
    while (getline(line, MAXLINE) > 0)
      if (strstr(line, argv[1]) != NULL) {
        printf("%s", line);
        found++;
      }
  return found;
}
```
The standard library function strstr(s,t) returns a pointer to the first occurrence of the string t in the string s, or NULL if there is none. Declared in <string.h>.

The model can now be elaborated to illustrate further pointer constructions. Suppose we want to allow two optional arguments. One says "print all lines except those that match the patter;" the second says "precede each printed line by its line number."

A common convention for C programs on UNIX systems is that an argument that begins with a minus sign introduces an optional flag or parameter. If we choose -x (for "except") to signal the inversion, and -n ("number") to request line numbering, then the command
```
  find -x -n pattern
```
will print each line that doesn't match the pattern, preceded by its line number.

Optional arguments should be permitted in any order, and the rest of the program should be independent of the number of arguments that were present. Furthermore, it is convenient for users if option arguments can be combines, as in find -nx pattern.

    *** See grep_program

argc is decremented and argv is incremented before each optional argument. At the end of the loop, if there are no errors, argc tells how many arguments remain unprocessed and argv points to the first of these. Thus argc should be 1 and *argv should point at the pattern. Since *++argv is a pointer to an argument string, so (*++argv)[0\] is its first character. Another way of doing it would be **++argv. Because [] binds tighter than * and ++, the parentheses are necessary; without them, the expression becomes *++(argv[0\]). In fact, that is what we used in the inner loop, where the task is to walk along a specific argument string. In the inner loop, the expression *++argv[0\] increments the pointer argv[0\].

It is rare that one uses pointer expressions more complicated than these; in such cases, breaking them into two or three steps will be more intuitive.


