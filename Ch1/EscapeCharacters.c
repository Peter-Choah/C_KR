#include <stdio.h>

/* replaces tabs, backspaces, and backslashes by their escape characters*/

int main(void){

    int c;

    putchar('\n');
    while ((c = getchar()) != EOF){
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\");
        else
            putchar(c);    
    }
}