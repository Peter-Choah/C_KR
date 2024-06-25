#include <stdio.h>
/*  print Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300*/

main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of tempereature */
    upper = 300;    /* upper limit */
    step = 20;      /* step size*/

    fahr = lower;
 
    char header[] = "Fahrenheit to Celsius Converter";     /* title of table */

    printf("%s\n", header);
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr-32);
        printf("%3.f\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    
}