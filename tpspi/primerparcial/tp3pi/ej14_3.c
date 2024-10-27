#include <stdio.h>
#include <limits.h>

int main(){
    int c, keepGoing = 1, lower = MAX_INT;
    while(keepGoing)
    {
        c = getchar();
        keepGoing = (isalpha(c) || c == ' ');
        if(c != ' '){
            lower = MIN(lower, c);
        }
    }
    return 0;
}

