/* Rewrite the routines day_of_year and month_day with pointers instead of
 * indexing. */

#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

static char *dayptr[2] = {daytab[0], daytab[1]};

int day_of_year(int year, int month, int day);

void month_day(int year, int yearday, int *month, int *day);

int main(void) {
  int yearday, month, day;

  yearday = day_of_year(1988, 2, 29);
  printf("%d\n", yearday);

  yearday = day_of_year(2020, 2, 31);
  printf("%d\n", yearday);

  month_day(1988, 60, &month, &day);
  printf("Month: %d, Day: %d\n", month, day);

  month_day(1999, 366, &month, &day);
  printf("Month: %d, Day: %d\n", month, day);

  return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
  int i, leap;

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; i < month; i++)
    day += *(dayptr[leap] + i);
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= *(dayptr[leap] + i);
  *pmonth = i;
  *pday = yearday;
}
