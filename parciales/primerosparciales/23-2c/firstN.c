
#define CHARS 256

void init_array(unsigned char array[], int dim, unsigned int initializer) {
    for (int i = 0; i < dim; ++i)
        array[i] = initializer;
}

void leave_seen(unsigned char arr[], int dim, unsigned char views[CHARS], int * newDim, int *del) {
    int i = 0, j = 0;
    while(i < dim){
        if(views[arr[i]] > 0) {
            arr[j++] = arr[i];
            --views[arr[i]];
        } else {
            ++*del;
        }
        ++i;
    }
    *newDim = j;
}

void firstN(unsigned char arr[], int dim, unsigned int n, int * newDim, int *del){
    *newDim = dim;
    *del = 0;
    if(dim == 0){
        return;
    }
    if(n == 0){
        *del = dim;
        *newDim = 0;
        return;
    }
    unsigned char views[CHARS];
    init_array(views, CHARS, n);
    // Moding this way allows us to initialize views in whatever we want
    // If to leave just n' vowels, we could just change init_array to do
    // it as we want to
    leave_seen(arr, dim, views, newDim, del);
}
#include <assert.h>
int main(void) {
   unsigned char v[] = {1, 2, 1, 3, 1, 4, 5, 2};
   int dim, del;
   firstN(v, 8, 3, &dim, &del); // dim es 8, del es 0, v no cambia
   assert(dim==8);
   assert(del==0);
   assert(v[0]==1 && v[1]==2 && v[2]==1 && v[3]==3 && v[4]==1 && v[5]==4 && v[6]==5 && v[7]==2);
   firstN(v, 8, 8, &dim, &del); // dim es 8, del es 0, v no cambia
   assert(dim==8);
   assert(del==0);
   assert(v[0]==1 && v[1]==2 && v[2]==1 && v[3]==3 && v[4]==1 && v[5]==4 && v[6]==5 && v[7]==2);
   firstN(v, 8, 4, &dim, &del); // dim es 8, del es 0, v no cambia
   assert(dim==8);
   assert(del==0);
   assert(v[0]==1 && v[1]==2 && v[2]==1 && v[3]==3 && v[4]==1 && v[5]==4 && v[6]==5 && v[7]==2);
   firstN(v, 8, 1, &dim, &del); // dim=5, del=3, v = {1, 2, 3, 4, 5};
       assert(dim==5);
   assert(del==3);
   assert(v[0]==1 && v[1]==2 && v[2]==3 && v[3]==4 && v[4]==5);
   
   unsigned char w[] = {1, 2, 1, 3, 1, 4, 5, 2};
   firstN(w, 8, 0, &dim, &del); // dim=0, del=8, w = {}
   assert(dim==0);
   assert(del==8);

   unsigned char t[] = {1, 2, 1, 3, 1, 4, 5, 2};
   firstN(t, 8, 2, &dim, &del); // dim=7, del=1, t = {1, 2, 1, 3, 4, 5, 2}
   assert(dim==7);
   assert(del==1);
   assert(t[0]==1 && t[1]==2 && t[2]==1 && t[3]==3 && t[4]==4 && t[5]==5 && t[6]==2);

   return 0;
}
