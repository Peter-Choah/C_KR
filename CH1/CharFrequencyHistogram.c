#include <stdio.h>

// Exercise 14
// Histogram of character frequency

int main(void){

    int frequencies[79] = {0};
    int c;

    while ((c = getchar()) != EOF){
        if (c == '\n' || c == '\t' || c == ' '){
            continue;
        }
        else {
            frequencies[c-48] += 1;
        }
    }

    for (int i = 48; i < 127; i++){
        putchar(i);
        printf(" %d ", frequencies[i-48]);
    }

    for (int i = 48; i < 127; i++){
        putchar(i);
        printf(" |");

        for (int j = 0; j < frequencies[i-48]; j++){
            putchar('-');
        }
        putchar('\n');
        
    }


}