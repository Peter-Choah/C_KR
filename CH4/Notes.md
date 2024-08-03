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


