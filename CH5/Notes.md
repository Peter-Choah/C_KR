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
