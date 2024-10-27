#include <stdio.h>
#include <assert.h>

int eliminaCeros(int v[], int n){
    int i = 0, j = 0;
    while (j < n){
         if (v[j] == 0){
            ++j;
        } else {
            v[i++] = v[j++];
        }
    }
    return i;
}

void printArr(const int v[], int dim){
    for(int i = 0; i < dim; ++i){
        printf("%d ", v[i]);
    }
    putchar('\n');
}

int main(){
    int s[] = { 0, 1, 0, 0, 3, 5, 0 };
    int t[10];
    int n = eliminaCeros(s, 7);
    printArr(s, n);
    assert(n == 3);
    return 0;
}

