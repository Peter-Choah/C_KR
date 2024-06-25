#include <stdio.h>

#define MAXLINE 1000
#define MINLINE 80

int getLines(char line[], int maxline, int minline);

// over 80 characters over 80 characters over 80 characters over 80 characters over 80 characters over 80 characters over 80 characters over 80 characters over 80 characters over 80 characters over 80 characters over 80 characters 

int main(void){
    int len;
    char line[MAXLINE];

    while ((len = getLines(line, MAXLINE, MINLINE)) > 0)
        if (len > 79) {
            printf("%s", line);
        }
    return 0;
}

/* getlines: read line into s, return length */
int getLines(char s[], int lim, int min){
    int c, i;

    i = 0;
    while(i < lim && (c = getchar()) != EOF && c != '\n'){
        s[i] = c;
        i++;
    }
    if (c == '\n'){
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}
