#include <stdio.h>
#define ES_VOCAL(a) ((a) == 'a' || (a) == 'A' || (a) == 'e' || (a) == 'i' || (a) == 'I' || (a) == 'o' || (a) == 'O' || (a) == 'u' || (a) == 'U')
#define GAP ('a' - 'A')
#define TO_LOWER(a) {if((a) <= 'Z' && (a) >= 'A'){\
						(a) = (a) + GAP;\
						}\
						}
/* 112000 */
int main(){

    int n = ES_VOCAL('a');// n vale 1
    printf("%d", n);

    n = ES_VOCAL('A') || ES_VOCAL('B');// n vale 1
    printf("%d", n);

    n = ES_VOCAL('a') + 1;// n vale 2
    printf("%d", n);

    /* *Aca lo que tiene que interpretar nuestra macro es que nos pasaron la b entiendo...* */
    n = ES_VOCAL('a' + 1);// n vale 0
    printf("%d", n);

    n = 1 - ES_VOCAL('a');// n vale 0
    printf("%d", n);

    n = ES_VOCAL('8');// n vale 0
    printf("%d", n);
}

