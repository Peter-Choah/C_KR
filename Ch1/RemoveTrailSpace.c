#include <stdio.h>

#define MAXLINE 1000

int getLines(char line[], int maxline);
int removeTrail(char line[], int length);

int main(void){
    char line[MAXLINE];
    int len = 0;
    int trails = 0;

    while ((len = getLines(line, MAXLINE)) > 0){ 
        trails = removeTrail(line, len);  // can be quicker by flagging it with trailings
        len = len - trails;
        if (len > 1){       // 1 removes empty lines as well
        printf("%s", line);
        }
    }
}

// gets lines
int getLines(char line[], int maxline){
    int c, i;
    for (i = 0; i < maxline && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

// remove trailing blanks from line
int removeTrail(char line[], int length){
    int trails = 0;     // amount of trails found
    while (line[length-2] == ' ' || line[length-2] == '\t' && length > 0){
        line[length-2] = '\n';
        line[length-1] = '\0';
        --length;
        ++trails;
    }

    return trails;
}