#include <stdio.h>

int main(){
    int c, space = 0;
    while((c = getchar()) != EOF){
        if(!space || c != ' ')
            putchar(c);
        if (c == ' ') {
            space = 1;
        } else {
            space = 0;
        }
    }
    return 0;
}

