/* Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent.*/

// engineering notation rather
#include <ctype.h>
#include <stdio.h>

double atof(char s[]);
void ftoa(char t[], double val);
double pow(double, double);

int main(int argc, char *argv[]) {
  char s[] = "-145.32e2";
  char t[100];

  printf("Double = %f\n", atof(s));
  ftoa(t, atof(s));
  printf("Engineering Notation = %s\n", t);
}

double atof(char s[]) {
  double val, power;
  int i, sign, exponent, exponent_sign;

  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (val = 0.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
  }
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  // handling scientific notation
  exponent_sign = exponent = 0;
  if (s[i] == 'e' || s[i] == 'E') {
    i++;
    exponent_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
      i++;
    for (exponent = 0; isdigit(s[i]); i++) {
      exponent = 10 * exponent + (s[i] - '0');
    }
  }

  double exponential = pow(10, exponent);
  if (exponent_sign == -1) {
    return (sign * val / power) / exponential;
  } else {
    return (sign * val / power) * exponential;
    ;
  }
}

/* Converts float to engneering notation assuming that the value is > 0 */
void ftoa(char t[], double val) {
  int i, j, sign;

  int exponent = 0;

  if (val < 0) {
    sign = -1;
  }
  // Get val less than 1000 and add to exponent
  while (val > 1000) {
    exponent += 3;
    val /= 1000;
  }
}

double pow(double x, double y) {
  double num = x;
  if (y < 1) {
    return 1;
  }
  while (y > 1) {
    num *= x;
    y--;
  }
  return num;
}
