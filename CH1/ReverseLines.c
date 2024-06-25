#include <stdio.h>

#define MAXLINE 1000

int getLines(char line[], int maxline);
void reverseLine(char line[], char reversedLine[], int lineLength);

// Prints each line and its subsequent reversed line
int main(void){
    char line[MAXLINE];
    char reversedLine[MAXLINE];
    int length;
    while ((length = getLines(line, MAXLINE)) > 0){
        reverseLine(line, reversedLine, length);
        printf("%s%s\n",  line, reversedLine);
    }
    return 0;
}

// get each line
int getLines(char s[], int maxline){
    int i, c;
    for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n'){
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

// reverses the line into another array, assumes that both arrays are of equal length
void reverseLine(char line[], char reversedLine[], int lineLength){
    int i;
    for (int i = 0; i < lineLength - 1; i++){   // lineLength - 1 to skip \0 and \n
        reversedLine[i] = line[lineLength - i - 2];
    }
    reversedLine[lineLength - 1] = '\n';
    reversedLine[lineLength] = '\0';
}