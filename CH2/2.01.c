#include <limits.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Data Type Size Limits\n");

  // char datatype
  printf("Size of char: %i bits\n", CHAR_BIT);
  printf("Max of unsinged char: %i\n", UCHAR_MAX);
  printf("Max of signed char: %i \n", SCHAR_MAX);
  printf("Min of signed char: %i \n", SCHAR_MIN);

  // short int datatype
  printf("Max of unsigned Short Int %i\n", USHRT_MAX);
  printf("Min Short Int: %i\n", SHRT_MIN);
  printf("Max Short Int: %i\n", SHRT_MAX);

  // int datatype
  printf("Max of unsigned INT %u\n", UINT_MAX);
  printf("Min Int: %i\n", INT_MIN);
  printf("Max Int: %i\n", INT_MAX);

  // long int datatype
  printf("Max of unsigned Long Int %lu\n", ULONG_MAX);
  printf("Min Long Int: %ld\n", LONG_MIN);
  printf("Max Long Int: %ld\n", LONG_MAX);
}
