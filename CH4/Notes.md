# Chapter 4 Functions and Program Structure

C programs generally consist of many small functions rather than a few big ones.

A program may reside in one or more source files.

Source files may be compiled separately and loaded together, along with previously compiled functions from libraries. The process varies from system to system.

Function declaration and definition in C follows the ANSI standard. It makes it possible for a compiler to detect many more errors and perform appropriate type coercions automatically.

The standard clarifies the rules on the scope of names. One in particular requires that there is only one definition of each external object. Initialization is more general: automatic arrays and structures may now be initialized.

The new C preprocessor also include a more complete set of conditional compilation directives, a way to create quoted strings from macro arguments, and better control over the macro expansion process.


## 4.1 Basics of Functions

If the return type is not specified, int is assumed.

A minimal function is 

  dummy() {}

which is useful as a placeholder.


A program is just a set of definitions of variables and functions. Communication between the functions is by arguments and values returned by the functions, and through external variables. The functions can occur in any order in the source file, and the source program can be split into multiple files, so long as no function is split.

The calling function is free to ignore the returned values. It is also unnecessary to have an expression after return, which then causes no value to be returned to the caller. Control is then returned to the caller with no value when execution "falls of the end" of the function by reaching the closing right brace. 

It is not illegal, but bad, if a function returns a value from one place and no value from another. If it fails to return a value, its "value" is certain to be garbage.

The returned status value from main, is available for use by the environment that called the program.

The mechanics of how to compile and load a C program that resides on multiple source files vary from one system to the next. ON UNIX, the cc command in CH 1 does the job. Suppose that there are 3 functions stored in 3 files called main.c, getline.c, and str index.c. Then the command

  cc main.c getline.c strindex.c

compiles the 3 files, placing the resulting object code in files main.o getline.o, and strindex.o, then loads them all into an executable file called a.out. If there is an error, say in main.c, that file can be recompiled by itself and the result loaded with the previous object files, with the command

  cc main.c getline.o strindex.o

The cc command uses the ".c" versus ".o" naming convention to distinguish source files from object files.


## 4.2 Functions Returning Non-integers

We know that function argument and return types are defined in function declarations/prototypes. Compilers can check if there are inconsistent types between functions in the same source file. However, they are not able to detect this error if the function is compiled from a different source file.

The reason this mismatch can happen is that if there is no function prototype, a function is implicitly declared by its first appearance in an expression, such as 
  sum += atof(line)

If a name that has not been previously declared occurs in an expression and is followed by a left parenthesis, it is declared by context to be a function name, the function is assumed to return an int, and nothing is assumed about its arguments.

E.g
  double atof();
This is taken that nothing is to be assumed about the arguments of atof; all parameter checking is turned off. Don't do this. 

If there are no arguments, use void.

## 4.3 External Variables

A C program consists of a set of external objects, which are either variables or functions.

External is variables defined out side functions and internal is vice versa.
By default, external variables and functions have the property that all references to them by the same name, even from functions compiled separately, are references to the same thing (external linkage).

Automatic variables which are internal to a function, come into existence when the function is entered, and disappear when it is left.
External variables are useful because they live permanently in the program compared to the automatic variables.

A Reverse Polish Calculator (RFP) works by having pushing operands and popping them when encountering an operator.

## 4.4 Scope Rules

Functions and external variables that make up a C program need not all be compiled at the same timel the source text of the program may be kept in several files, and previously compiled routines may be loaded from libraries.
Among the questions of interest are:

- How are declarations written so that variables are properly declared during compilation?
- How are declarations arranged so that all the pieces will be properly connected when the program is loaded?
- How are declarations organized so that there is only one copy?
- How are external variables initialized?

The 'scope' of a name is the part of the program within which the name can be used. For an automatic variable declared at the beginning of a function, the scope is the function in which the name is declared. Local variables of the same name in different functions are unrelated. The same is true of the parameters of the function, which are in effect local variables.
Basically, all variables in a function are private, unrelated to other variables with the same name outside of the function.

The scope of an external variable or a function lasts from the point at which it is declared to the end of the file being compiled.
Functions before the declaration of a variable are not able to use that variable.

If an external variable is to be referred to before it is defined, or if it is defined in a different source file from the one where it is being used, then an 'extern' declaration is mandatory.

The declaration and definition of an external variable is different. A declaration announces the properties of a variable (usually its type). A definition also causes storage to be set aside.

  int sp;
  double val[MAXVAL];
If the above lines appear outside of any function, they define the external variables sp and val, cause storage to be set aside, and also serve as the declaration for the rest of that source file. 

  extern int sp;
  extern double val[];
OTOH, these lines declare for the rest of the source file that sp is an int and that val is a double array (whose size is determined elsewhere), but they do not create the variables or reserve storage for them.

There must be only one definition of an external variable among all the files that make up the source program; other files may contain extern declarations to access it. (There may also be extern declarations in the file containing the definition.) Array sizes must be specified with the definition, but are optional with an extern declaration.

Initialization of an external variable goes only with the definition.

Although it is not a likely organization for this program, the functions push and pop could be defined in one file, and the variables val and sp defined and initialized in another. Then these definitions and declarations would be necessary to tie them together:

  In file1:
    extern int sp;
    extern double val[];

    void push(double f) {...}

    double pop(void) {...}

  In file2:
    int sp = 0;
    double val[MAXVAL];

Because the extern declarations if file1 lie ahead of and outside the function definitions, they apply to all functions; one set of declarations suffices for all of file1. This same organizations would also be needed if the definitions of sp and val followed their use in one file.

## 4.5 Header Files

Dividing the calculator program into several source files:

- main.c (with the main function)
- stack.c (push, pop, and their variables)
- getop.c (getop function)
- getch.c (getch and ungetch)

They are separated because they would come from a separately-compiled library in a realistic program.

One thing to worry about - the definitions and declarations shared among files. Centralizing is important so that there is only one copy to be updated among all the files.
Accordingly, this common material will be placed in a *header file*, calc.h, which will be included as necessary.

 ** See image to get a better idea, pg 96

There is usually a tradeoff between each file having access only to the information it needs for its job and the practical reality that it is harder to maintain more header files.
Up to some moderate program size, it is probably easy enough to have 1 header file that contains everything to be shared between any two parts of the program.

## 4.6 Static Variables

Variables sp, val, buf, and bufp are for private use of functions in their respective source files and not meant to be accessed by anything else.
The static declaration, applied to an external variable or function, limits the scope of that object to the rest of the source file being compiled. External static provides a way to hide names like buf and bufp in the getch-ungetch combination, which must be external so they can be shared, yet which should not be visible to users of getch and ungetch.

Static storage is specified by prefixing the normal declaration with 'static'. If the two routines and two variables are compiled in 1 file:

  static char buf[BUFSIZE]; /* buffer for ungetch */
  static int bufp = 0; /* next free position in buf*/

  int getch(void){...}

  void ungetch(int c) {...}

then no other routine will be able to access buf and bufp, and those names will not conflict with the same names in other files of the same program. Similarly, the variables of push and pop, sp and val, can be hidden by declaring the variables to be static.

The external static declaration is usually used for variables but can also be applied to functions. Normally, function names are global, but if declared static, its name is invisible outside of the file which it is declared.

The static declaration can also be applied to internal variables, turning automatic variables into static internal variables. These are persistent between function calls.

It's good to preserve state across multiple function calls while still having encapsulation. Likely problematic in multi-threaded programs though.

## 4.7 Register Variables

A register declaration advises the compiler that the variable in question will be heavily used. The idea is that register variables are to be placed in machine registers, which may result in smaller and faster programs. Compilers are free to ignore the advice.

The register declaration can only be applied to automatic variables and to the formal parameters of a function.
  register int x;
  register char c;

  f(register unsigned m, register long n){
    register int ;
    ...
  }

In practice, there are restrictions on register variables, reflecting the realities of underlying hardware. Only few variables in each function may be kept in registers, and only certain types are allowed. These restrictions on number and types of register variables vary from machine to machine. It is also not possible to take the address of a register variable.

## 4.8 Block Structure

Functions are not block-structured as they may not be defined within other functions. Variables can be defined in a block-structured fashion within a function.

Declarations of variables may follow the left brace that introduces any compound statement, not just the one that begins a function. Variables declared in this way hide any identically named variables in outer blocks, and remain in existence until the matching right brace.

  if (n > 0) {
    int i;
    for (i = 0; i< n; i++)
      ...
  }

The scope of i is the "true" branch of the if; this i is unrelated to any i outside the block. An automatic variable declared and initialized in a block is initialized each time the block is entered. A static variable is initialized only the first time the block is entered.

Automatic variables, formal parameters, also hide external variables and functions of the same name.
E.g:

  int x;
  int y;
  
  f(double x){
    double y;
    ...
  }

Within the function f, occurences of x refer to the parameter, which is double; outside of f, they refer to the external int. Same for y.

## 4.9 Initialization
Summary of the rules of initialization.

In the absence of explicit initialization, external and static variables are guaranteed to be initialized to 0; automatic and register variables have garbage initial values.

Scalar variables may be initialized when they are defined, by following the name with an equals sign and an expression:

  int x = 1;
  char squote = '\'';
  long day = 1000L * 60L * 60L * 24L; /* milliseconds/day */

For external and static variables, the initializer must be a constant expression; the initialization is done once, conceptually before the program begins execution.
For automatic and register variables, it is done each time the function or block is entered.

For automatic and register variables, the initializer is not restricted to being a constant: it may be any expression involving previously defined values, even function calls. Look at this binary search

  int binsearch(int x, int v[], int n){
    int low = 0;
    int high = n - 1; /* initializing with n - 1 is possible
    int mid;
    ...
  }

instead of

  int low, high, mid;
  low = 0;
  high = n - 1;

In effect, initializations of automatic variables are just shorthand for assignment statements. Explicit assignments are used more generally because initializers in declarations are harder to see and further away from the point of use.

An array may be initialized by following its declaration with a list of initializers enclosed in braces and separated by commas.

  int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

The compiler will compute the length by counting the initializers if there is no explicit size of array. 12 in this case.

If there are fewer initializers for an array than the number specified, the missing elements will be 0 for external, static, and automatic variables. It is an error to have too many initializers. There is no way to specify repetition of an initializer, nor to initialize an element in the middle of an array without supplying all the preceding values as well.

Character arrays are cool; a string may be used instead of the braces and commas notaion;

  char pattern[] = "ould";

is equivalent to

  char pattern[] = { 'o', 'u', 'l', 'd', '\0' };

Array size of the above is five.

## 4.10 Recursion

Functions can call itself directly or indirectly.

Consider printing a number as a character string. As before, the digits are generated in the wrong order and needed to be reversed.
There are 2 solutions to this problem. 1st is to store the digits in an array as they are generated then print them in reverse order. 2nd is a recursive solution, in which printd first calls itself to cope with any leading digits, then prints the trailing digit.

#include <stdio.h>

/* printd: print n in decimal */
void printd(int n)
{
  if (n < 0) {
    putchar('-');
    n = -n;
  }
  if (n / 10)
    printd(n / 10);
  putchar(n % 10 + '0');
}
// This fails for the largest negative number as well.

When a function calls itself recursively, each invocation gets a fresh set of all the automatic variables, independent of the previous set. Thus, in printd(123) the first printd receives the argument n = 123. It passes 12 to a second printd, which in turn passes 1 to a third. The third-level printd() prints 1, then returns to the second level. That printd prints 2, then returns to the first level. That one prints 3 and terminates.

Another example of recursion is quicksort. Given an array, one element is chosen and the others are partitioned into two subsets - those less than the partition element and those greater than or equal to it. The same process is then applied recursively to the subsets. Recursion stops when a subset has fewer than two elements.

Using the middle element of each subarray for partitioning:
```
/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right)
{
  int i, last;
  void swap(int v[], int i, int j);
  
  if (left >= right)                  /* do nothing if array contains fewer than two elements */
    return;                           
  swap(v, left, (left + right)/2);    /* move partition elem to v[0]*/
  last = left;                        
  for (i = left+1; i <= right; i++)   /* partition */
    if (v[i] < v[left])
      swap(v, ++last, i);
  swap(v, left, last);                /* restore partition elem*/
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
```

Or just use standard library qsort which can sort objects of any type.

Recursion code is usually more compact and often much easier to write and understand than the non-recursive equivalent. Recursion is especially convenient for recursively defined data structures like trees.

## 4.1 The C Preprocessor

C provides certain language facilities by means of a preprocessor, which is conceptually a separate first step in compilation. The two most frequently used features are #include, to include the contents of a file during compilation, and #define, to replace a token by an arbitrary sequence of characters. Other features described in this section include conditional compilation and macros with arguments.

### 4.11.1 File Inclusion

File inclusion makes it easy to handle collections of #defines and declarations. Any source line of the form
  #include "filename"
or
  #include ```<filename>```

is replaced by the contents of the file filename. If the filename is quoted, searching for the file typically begins where the source program was found; if it is not found there, or if the name is enclosed in < and >, searching follows an implementation-defined rule to find the file. An included file may itself contain #include lines.

There are often several #include lines at the beginning of a source file, to include common #define statements and extern declarations, or to access the function prototype declarations for library functions from headers like <stdio.h>.

#include is the preferred way to tie the declarations together for a large program. It guarantees that all the source files will be supplied with the same definitions and variable declarations, and thus eliminates a particularly nasty kind of bug. When an included file is changed, all files that depend on it must be recompiled.

### 4.11.2 Macro Substitution
Definition has the form
// #define  name  replacement text

Occurrences of the token name will be replaced by the replacement text. A long definition can be continued onto several lines by placing a \ at the end of each line to be continued. The scope of a name defined is from its point of definition to the end of the source file being compiled. A definition may use previous definitions. Substitutions are made only for tokens, and do not take place within quoted strings. For example, if YES is a defined name, there would be no subsitituion in printf("YES") or in YESMAN.
Any name may be defined with any replacement text. For example,

  #define forever for (;;) /* infinite loop */

defines forever as an infinite loop.

It is possible to define macros with arguments, so the replacement text can be different for different calls of the macro.

  #define max(A, B) ((A) > (B) ? (A) : (B))

Although it looks like a function call, a use of max expands into in-line code. Each occurrence of a formal parameter (A or B here) will be replaced by the corresponding actual argument. Thus the line

  x = max(p+q, r+s);

will become

 x = ((p+q) > (r+s) ? (p+q) : (r+s));

So long as the arguments are treated consistently, this macro will serve for any data type; there is no need for different kinds of max for different data types, as there would be with functions.

Problems with this is that the expressions are evaluated twice, which is bad if they involve side effects like increment operators or input and output.

  max(i++, j++) /* increments the larger value twice */

Another problem is that you have to make sure the order of evaluation is preserved.

  #define square(x) x * x

is invoked as square(z+1).

  z+1 * z+1

A practical example of macros can be seen in <stdio.h> in which getchar are putchar are often defined as macros to avoid the run-time overhead of a function call per character processed. The functions in <ctype.h> are also usually implemented as macros.

Names may be undefined with #undef, usually to ensure that a rountine is really a function, not a macro:

  #undef getchar

  int getchar(void) {...}

Formal parameters are not replaced within quoted strings. If a parameter name is preceded by a # in the replacement text, the combination will be expanded into a quoted string with the parameter replaced by the actual argument. This can be combined with string concatenation to make longer strings like a debugging print macro:

  #define dprint(expr) printf(#expr " = %g\n", expr)

When invoked like

  dprint(x/y);

the macro is expanded into

  printf("x/y" " = %g\n", x/y);

and the strings are concatenated so the effect is

  printf("x/y = %g\n", x/y);

Within the actual argument, each " is replaced by \" and each \ by \\, so the result is a legal string constant.

The preprocessor operator ## provides a way to concatenate actual arguments during macro expansion.
If a parameter in the replacement text is adjacent to a ##, the parameter is replaced by the actual argument, the ## and surrounding white space are removed, and the result is re-scanned.
E.g. the macro paste concatenates its two arguments:

  #define paste(front, back) front ## back

so paste(name, 1) creates the token name1.

Rules for nested uses of ## are arcane.

### 4.11.3 Conditional Inclusion

It is possible to control preprocessing itself with conditional statements that are evaluated during preprocessing. This provides a way to include code selectively, depending on the value of conditions evaluated during compilation.

The #if line evaluates a constant integer expression (which may not include sizeof, casts, or enum constants). If the expression is non-zero, subsequent lines until an #endif or #elif or #else are included. The expression defined(name) in a #if is 1 if the name has been defined, and 0 otherwise.

E.g making sure that contents of a file hdr.h are included only once, the contents of the file are surrounded with a conditional like this:

  #if !defined(HDR)
  #define HDR

  /* contents of hdr.h go here */

  #endif

The 1st inclusion of hdr.h defines the name HDR; subsequent inclusions will find the name defined and skip down to #endif. A similar style can be used to avoid including files multiple times. If this style is used consistently, then each header can itself include any other headers on which it depends, without the user of the header having to deal with the interdependence.o

This sequence tests the name SYSTEM to decide which version of a header to include:

  #if SYSTEM == SYSV
    #define HDR "sysv.h"
  #elif SYSTEM == BSD
    #define HDR "bsd.h"
  #elif SYSTEM == MSDOS
    #define HDR "msdos.h"
  #else
    #define HDR "default.h"
  #endif
  #include HDR

The #ifdef and #ifndef lines are specialized forms that test whether a name is defined. The first example of #if above could have been written

  #ifndef HDR
  #define HDR

  /* contents of hdr.h go here */

  #endif


