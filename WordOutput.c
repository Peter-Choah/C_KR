#include <stdio.h>

#define IN 1     /* inside a word */
#define OUT 0    /* outside a word*/

int main(void)
{
    int state  = OUT;
    int c = 0;

    while((c = getchar()) != EOF){
        if (c != ' ' && c != '\n' && c != '\b')
        {
            state = IN;
            putchar(c);
        }
        else if (state == OUT)
            continue;
        else
        {
            state = OUT;
            putchar('\n');
        }
    }

}