#include <stdlib.h>
#include "polyADT.h"

// Esto lo estoy haciendo asi porque dicen que es una lista sin header
// Pero yo lo haria con header y que sea null si esta vacia
struct polyCDT {
    char isEmpty;
    int degree;
    float coef;
    struct polyCDT * next;
};

polyADT newPolynomial(void) {
    polyADT new = calloc(1, sizeof(struct polyCDT));
    new->isEmpty = 1;
    return new;
}

int isEmpty(polyADT poly) {
    return poly->isEmpty;
}

polyADT addTermRec(polyADT poly, float coef, int degree, int * added) {
    if (poly == NULL || poly->degree < degree) {
        polyADT new = calloc(1, sizeof(*new));
        new->coef = coef;
        new->degree = degree;
        new->next = poly;
        *added = 1;
        return new;
    } else if (poly->degree > degree) {
        poly->next = addTermRec(poly->next, coef, degree, added);
        return poly;
    }
    *added = 0;
    return poly;
}

int addTerm(polyADT *poly, float coef, int degree) {
    if (*poly == NULL) {
        return 0;
    }
    int added = 0;
    *poly = addTermRec(*poly, coef, degree, &added);
    return added;
}

polyADT addPolynomialRec(polyADT p, polyADT q) {
    if (p != NULL && q != NULL) {
        polyADT new = calloc(1, sizeof(*new));
        if (p->degree > q->degree) {
            new->degree = p->degree;
            new->coef = p->coef;
            new->next = addPolynomialRec(p->next, q);
            return new;
        } else if (p->degree < q->degree) {
            new->degree = q->degree;
            new->coef = q->coef;
            new->next = addPolynomialRec(p, q->next);
            return new;
        }
        new->degree = p->degree;
        new->coef = p->coef + q->coef;
        return new;
    } else if (p != NULL) {
        polyADT new = calloc(1, sizeof(*new));
        new->degree = p->degree;
        new->coef = p->coef;
        new->next = addPolynomialRec(p->next, q);
        return new;
    } else if (q != NULL) {
        polyADT new = calloc(1, sizeof(*new));
        new->degree = q->degree;
        new->coef = q->coef;
        new->next = addPolynomialRec(p, q->next);
        return new;
    }
    return NULL;
}

polyADT addPolynomial(polyADT p, polyADT q) {
    if ((p == NULL && q == NULL) || (p->isEmpty && q->isEmpty))
        return NULL;
    return addPolynomialRec(p, q);
}


