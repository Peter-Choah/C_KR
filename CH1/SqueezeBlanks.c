#include <stdio.h>

/* squeezes blanks thats more than 1 */

int main(void){

    int c;
    int blankCount = 0;

    while ((c=getchar()) != EOF)

        if (c == ' ')
        {
            if (blankCount < 1)
                putchar(c);
            blankCount += 1;
            
        }
        else
        {
            blankCount = 0;
            putchar(c);
        }
}