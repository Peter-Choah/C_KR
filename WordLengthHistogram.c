/*Exercise 1-13*/
#include <stdio.h>

#define IN 1
#define OUT 0
#define MAXCHAR 25
#define MAXLENGTH 90

// prints a histogram of length of words, doesn't account for same words happening twice
/*
int main(void) {
    
    int c, state, length;
    state = OUT;
    int charCount[MAXCHAR];

    for (int i = 0; i <= MAXCHAR; i++){
        charCount[i] = 0;
    }

    while ((c = getchar()) != EOF){
        if (c == ' ' || c == '\n' || c == '\t'){
            if (state == IN){
                charCount[length]++;
                length = 0;
                state = OUT;
            }
            continue;
        }
        else {
            state = IN;
            length++;
        } 
    }

    // format output histogram 
    for (int i = 1; i <= MAXCHAR; i++){
        printf("%4d | ", i);
        for (int j = 1; j <= charCount[i]; j++){
            putchar('*');
        }
        putchar('\n');
    }

    putchar('+'); 

    for (int i = 0; i <= MAXCHAR; i++){
        putchar('-');
    }
}
*/

// prints a vertical histogram, runs through the file twice

int main(void) {
    
    int c, state, length;
    state = OUT;
    int charCount[MAXCHAR];

    for (int i = 0; i <= MAXCHAR; i++){
        charCount[i] = 0;
    }

    while ((c = getchar()) != EOF){
        if (c == ' ' || c == '\n' || c == '\t'){
            if (state == IN){
                charCount[length]++;
                length = 0;
                state = OUT;
            }
            continue;
        }
        else {
            state = IN;
            length++;
        } 
    }

    // format output histogram 
    for (int i = MAXLENGTH; i >= 1; i--){
        printf("%3d |", i);
        for (int j = 1; j <= MAXCHAR; j++){
            if (charCount[j] >= i){     // print * if the charactercount is higher than the i-th level
                printf("  *");
            }
            else {
                printf("   ");          // spaces appropriately otherwise
            }
        }
        putchar('\n');
    }   
    
    // x-axis
    printf("    +");

    for (int i = 1; i <= MAXCHAR; i ++){
        printf("---");
        
    }

    putchar('\n');
    printf("     ");

    for (int i = 1; i <= MAXCHAR; i++){
        printf("%3d", i);
    }

    putchar('\n');  
}
