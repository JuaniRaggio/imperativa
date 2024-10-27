#include <stdio.h>
#include <assert.h>

int strend(char * s, char * t);

int main(void) {
  assert(strend("","")==1);
  assert(strend("something","")==1);
  assert(strend("something","thing")==1);
  assert(strend("something","something")==1);
  assert(strend("something","plus something")==0);
  assert(strend("not at the eeeeeend"," end")==0);
  assert(strend("not at the eeeeeennnnnd","end")==0);
  assert(strend("","s")==0);
  assert(strend("ssss","sss")==1);
  assert(strend("ssss","sssss")==0);
  puts("OK!");
  return 0;
}

#define TOP 100

int cmp_from_end(char * s, char * t, int i){
    int j = 0;
    while(s[i++] == t[j++] && s[i] != '\0' && t[j] != '\0');
    return s[i] == '\0' && t[j] == '\0';
}

int strend(char * s, char * t) {
    int found = 1;

    if(t[0] == '\0')
        return found;
    found = 0;
    for(int i = 0; !found && s[i] != '\0' && i <= TOP; ++i){
        if(s[i] == t[0]){
            found = cmp_from_end(s, t, i);
        }
    }
    return found;
}


