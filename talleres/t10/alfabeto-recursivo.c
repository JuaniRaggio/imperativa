#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
 
bool alfabeto(const char *s);
 
int main() {
    assert(alfabeto("a,b,c") == 1);
    assert(alfabeto("a,g,c") == 0);
    assert(alfabeto("a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z") == 1);
    assert(alfabeto("a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,a") == 0);
    assert(alfabeto("z") == 1);
    assert(alfabeto("z,a") == 0);
    assert(alfabeto("a,z") == 1);
    assert(alfabeto("a,a,a,a,a") == 0);
    assert(alfabeto("c,i,a") == 0);
    assert(alfabeto("b,b,c") == 0);
    
    puts("OK!");
    return 0;
}

bool alfabeto(const char * s) {
    if (s[1] == '\0')
        return true;
    if (s[0] < s[2])
        return alfabeto(s + 2);
    else
        return false;
}

