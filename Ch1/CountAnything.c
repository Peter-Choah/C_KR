#include <stdio.h>

/* count any character */

#define CHAR '\n' /* insert character to count here*/


int main(void){

    int c, count;
    count = 0;

    while ((c = getchar()) != EOF)
        if (c == CHAR)
            count++;

    printf("%d\n", count);

}