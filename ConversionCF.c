#include <stdio.h>
/* Print Celsius to Fahrenheit table
    for celsius 0, 10, ..., 150 */

main(){

    float fahr, celsius;

    int lower, upper, step;

    lower = 0;
    upper = 150;
    step = 10;

    celsius = lower;

    char header[] = "Celsius to Fahrenheit";

    printf("%s\n",header);
    printf("Celsius\tFahrenheit\n");
    while (celsius <= upper){
        fahr = celsius * (9.0 / 5.0) + 32;
        printf("%3.0f\t%6.1f\n", celsius, fahr);
        celsius += step;
    }

}