#include <stdio.h>

#define IN 1
#define OUT 0

void blankFunction();

// remove comments,
// conditions for a comment are //, /*, */
// comments do not nest
// buffer is 1 character in front
int main(void){

    int buffer, commentline, commentblock, c;
    int buffering, ccount;

    while ((buffer = getchar()) != EOF){
        // buffers to skip printing the end of the comment block
        if (buffering == IN){
            buffering = OUT;
            c = buffer;
            continue;
        }

        if (ccount < 2 && c == '\n'){
            c = buffer;
            continue;
        }
        // removes unncessary newlines
        if (c == '\n' && buffer == '\n'){
            continue;
        }

        // check if comment line
        if (commentline == IN){
            while ((buffer = getchar()) != '\n'){
                continue;
            }
            c = buffer;
            commentline = OUT;
        }

        // check if in comment block
        if (commentblock == IN){
            while (((buffer = getchar()) != '/') && c != '*'){
                    c = buffer;
                }
                commentblock = OUT;
                c = buffer;
                buffering = IN;
                continue;
            }

        // check for start of comment line
        if (c == '/' && buffer == '/'){
            commentline = IN;
            continue;    
        }

        // check for start of comment block
        else if (c == '/' && buffer == '*'){
            commentblock = IN;
            continue;
        }

        // prints c if passes all checks
        putchar(c);
        if (c == '\n'){
            ccount = 0;
        }

        ccount++;

        c = buffer;
    }

    // last character buffer check
    if (commentblock != IN && commentline != IN){
        putchar(buffer);
    }
}


/* comment block */

void blankFunction(){
    printf("blank");
}