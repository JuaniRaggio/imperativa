#include <stdio.h>

int main(){
    int digits, i = 0, d = 0, coma = 0;
    while(((digits = getchar()) != '\n') && digits != '\0'){
        if(digits == ',')
            coma = 1;
        else if(!ISNUM(digits)){
            printf("There is a non-numeric digit");
            return -1;
        } else if((digits - '0')%10 == 5)
            (coma ? d:i)++;
    }
    printf("There are %d fives on the integer side, and %d fives on the decimal side", i, d);
    return 0;
}

