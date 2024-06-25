
#include <float.h>
#include <limits.h>
#include <stdio.h>

int main() {
  float flt_a, flt_b, flt_c, flt_r, flt_m;

  /* FLOAT */
  printf("\nFLOAT MAX\n");
  printf("<limits.h> %E  ", FLT_MAX);

  flt_a = 2.0;
  flt_b = 1.0;
  while (flt_a != flt_b) {
    flt_m = flt_b; /* MAX POWER OF 2 IN MANTISSA */
    flt_a = flt_b = flt_b * 2.0;
    flt_a = flt_a + 1.0;
  }
  flt_m = flt_m + (flt_m - 1); /* MAX VALUE OF MANTISSA */

  flt_a = flt_b = flt_c = flt_m;
  while (flt_b == flt_c) {
    flt_c = flt_a;
    flt_a = flt_a * 2.0;
    flt_b = flt_a / 2.0;
  }
  printf("COMPUTED %E\n", flt_c);
}
