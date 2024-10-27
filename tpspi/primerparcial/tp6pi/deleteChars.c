#include <stdio.h>
#include <assert.h>
#include <string.h>

void
deleteChars(char * s1, char * s2);

int main(void) {
    
  char s3[] = "abc";
  char s4[] = "axc123456789012345678901234567890";
  deleteChars(s3,s4);
  assert(strcmp(s3, "b")==0);
  assert(strcmp(s4, "x123456789012345678901234567890")==0);

  char s1[] = "Hola, soy un string";
  char s2[] = "Yo soy otro string";

  deleteChars(s1, s2);
  assert(strcmp(s1, "Hla, sy un string")==0);
  assert(strcmp(s2, "Y soy tro string")==0);

  char empty[] = "";
  deleteChars(s1, empty);
  assert(strcmp(s1, "Hla, sy un string")==0);
  assert(strcmp(empty, "")==0);

  strcpy(s1, "ABCDE");
  strcpy(s2, "abcde");
  deleteChars(s1, s2);
  assert(strcmp(s1, "ABCDE")==0);
  assert(strcmp(s2, "abcde")==0);

  deleteChars(s1,s1);
  assert(strcmp(s1, "")==0);
  
  /* char s3[] = "abc"; */
  /* char s4[] = "axc123456789012345678901234567890"; */
  deleteChars(s3,s4);
  assert(strcmp(s3, "b")==0);
  assert(strcmp(s4, "x123456789012345678901234567890")==0);


  puts("OK!");
  return 0;
}

void fill_str(char * s, int i, int from) {
    do{
        s[i] = s[from++];
    } while(s[i++] != '\0');
}

void deleteChars(char * s1, char * s2){
    int i, j, w;
    for(i = 0, j = 0, w = 0; s1[w] != '\0' && s2[w] != '\0'; ++w) {
        if(s1[w] != s2[w])
        {
            s1[i++] = s1[w];
            s2[j++] = s2[w];
        }
    }
    fill_str(s1, i, w);
    fill_str(s2, j, w);
}


