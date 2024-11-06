#include <stdlib.h>
#include "bstADT.h"

struct node {
    elemType value;
    struct node * left;
    struct node * right;
};

struct bstCDT {
    struct node * root;
    struct node * inorderIterator;
    struct node * preorderIterator;
    struct node * postorderIterator;
    size_t nodeCounter;
    size_t treeHeight;
    cmp fx;
};

bstADT newBst(cmp fx) {
    bstADT newTree = calloc(1, sizeof(struct bstCDT));
    newTree->fx = fx;
    return newTree;
}

void freeBstRec(struct node * root) {
    if (root == NULL) return;
    freeBstRec(root->left);
    freeBstRec(root->right);
    free(root);
}

void freeBst(bstADT bst) {
    freeBstRec(bst->root);
    free(bst);
}

// Cantidad de nodos en el arbol
unsigned int size(const bstADT bst) {
    return bst->nodeCounter;
}

// Devuelve la altura del arbol (la longitud de la rama mas larga)
// Un arbol vacio tiene altura 0
unsigned int height(const bstADT bst) {
    return bst->treeHeight;
}

int belongsRec(struct node * root, cmp fx, elemType element) {
    int comparison;
    if (root == NULL) return 0;
    if ((comparison = fx(root->value, element)) == 0) return 1;
    struct node * aux = comparison < 0 ? root->right:root->left;
    return belongsRec(aux, fx, element);
}

// Retorna 1 si el elemento estaก en el arbol, cero si no esta
int belongs(const bstADT bst, elemType elem) {
    return belongsRec(bst->root, bst->fx, elem);
}

struct node * insertRec(struct node * root, cmp fx, elemType element, int * added, size_t * height) {
    int comparison;
    if (root == NULL) {
        struct node * newNode = calloc(1, sizeof(struct node));
        newNode->value = element;
        ++*height;
        *added = 1;
        return newNode;
    } else if ((comparison = fx(root->value, element)) == 0) {
        *added = 0;
        return root;
    }
    ++*height;
    if (comparison < 0) {
        root->right = insertRec(root->right, fx, element, added, height);
    } else {
        root->left = insertRec(root->left, fx, element, added, height);
    }
    return root;
}

// Agrega un elemento respetando el orden
// Retorna 1 si lo pudo agregar (no estaba), cero si no (ya estaba)
int insert(bstADT bst, elemType elem) {
    int added = 0;
    size_t height = 0;
    bst->root = insertRec(bst->root, bst->fx, elem, &added, &height);
    bst->nodeCounter += added;
    if (height > bst->treeHeight) bst->treeHeight = height;
    return added;
}

void inorderRec(elemType * orderedVector, size_t * idx, struct node * root) {
    if (root == NULL) return;
    // 1. copiar el de la izquierda
    inorderRec(orderedVector, idx, root->left);
    // 2. copiar el actual
    orderedVector[(*idx)++] = root->value;
    // 3. copiar el de la derecha
    inorderRec(orderedVector, idx, root->right);
}

// Retorna un vector con los elementos almacenados de acuerdo a un recorrido inorder
// La cantidad de elementos del vector esta dada por la funcion size
elemType * inorder(const bstADT bst) {
    if (bst->nodeCounter == 0) return NULL;
    elemType * orderedVector = malloc(sizeof(elemType) * bst->nodeCounter);
    size_t idx = 0;
    inorderRec(orderedVector, &idx, bst->root);
    return orderedVector;
}


void preorderRec(elemType * preorderVector, size_t * idx, struct node * root) {
    if (root == NULL) return;
    preorderVector[(*idx)++] = root->value;
    preorderRec(preorderVector, idx, root->left);
    preorderRec(preorderVector, idx, root->right);
}

elemType * preorder(const bstADT bst) {
    if (bst->nodeCounter == 0) return NULL;
    elemType * preorderVector = malloc(sizeof(elemType) * bst->nodeCounter);
    size_t idx = 0;
    preorderRec(preorderVector, &idx, bst->root);
    return preorderVector;
}

void postorderRec(elemType * postorderVector, size_t * idx, struct node * root) {
    if (root == NULL) return;
    postorderRec(postorderVector, idx, root->left);
    postorderRec(postorderVector, idx, root->right);
    postorderVector[(*idx)++] = root->value;
}

elemType * postorder(const bstADT bst) {
    if (bst->nodeCounter == 0) return NULL;
    elemType * postorderVector = malloc(sizeof(elemType) * bst->nodeCounter);
    size_t idx = 0;
    postorderRec(postorderVector, &idx, bst->root);
    return postorderVector;
}

/* struct node * deleteRec(struct node * root, cmp fx, int * deleted, size_t * height) {} */
/*  */
/* int delete(bstADT bst, elemType element) { */
/*     int deleted = 0; */
/*     size_t height = 0; */
/*     bst->root = deleteRec(bst->root, bst->fx, &deleted); */
/*     bst->nodeCounter -= deleted; */
/*     if () */
/*     return deleted; */
/* } */

// Mas avanzado aun: verificar si es balanceado por altura o no, crear iteradores inorder, preorder, postorder

