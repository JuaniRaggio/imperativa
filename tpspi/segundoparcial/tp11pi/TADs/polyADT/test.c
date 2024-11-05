#include <stdio.h>
#include "polyADT.h"


int main(void) {
    polyADT p1, p2, p3;
    p1 = newPolynomial();
    addTerm(&p1, 5, 10);
    addTerm(&p1, -3, 100);
    p2 = newPolynomial();
    addTerm(&p2, 6, 100);
    addTerm(&p2, -7, 20);

    p3 = addPolynomial(p1, p2); // p3 representa 3x¹⁰⁰ - 7x²⁰ + 5x¹⁰
    printf("OK!\n");
}

