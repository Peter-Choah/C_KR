#include <stdio.h>

#define MAXLINE 1000
#define FOLD 40
#define TABSPACE 4
#define IN 1
#define OUT 0

// folds long lines, also accounts for tabs
int main(void){
    int c, col, state;
    char line[MAXLINE];


    while((c = getchar()) != EOF){
        
        if (c == '\t'){
            for (int i = 0; i < 4; i++)
                putchar(' ');
            col += 4; 
            state = OUT;
        }
        else if (c == '\n'){
            putchar(c);
            col = 0;
            state = OUT;
        }
        else if (c == ' '){
            putchar(c);
            col++;
            state = OUT;
        }
        else{
            if (col > FOLD){
                putchar('\n');
                col = 0;
                putchar(c);
                state = IN;
            }
            else if (col == FOLD){
                if (state == IN){
                    printf("-\n");
                    putchar(c);
                    col = 1;
                    state = IN;
                }
                else{
                    putchar('\n');
                    putchar(c);
                    col = 1;
                    state = IN;
                }
            }
            else{
                putchar(c);
                col++;
                state = IN;
            }
        }
    }
    putchar('\n');
}