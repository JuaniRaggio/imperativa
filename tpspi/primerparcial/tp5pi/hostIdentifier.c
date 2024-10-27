#include <stdio.h>
#include <math.h>
#define BASE 2
#define IPBITS 32
#define BYTE 0xFF

unsigned long getmask(unsigned int bits){
    unsigned long mask = 0;
    do{
        mask += pow(BASE, bits--);
    } while(bits);
    return mask;
}

void hostIdentifier(unsigned long ip, unsigned char bitsNet){
    int masksize = IPBITS - bitsNet;
    unsigned long mask = getmask(masksize), host = ip & mask;
    ip = ip - host;
    printf("Network number: %lu.%lu.%lu.%lu\n", (ip >> 24) & BYTE, (ip >> 16) & BYTE, (ip >> 8) & BYTE, ip & BYTE);
    printf("Host number: %lu.%lu.%lu.%lu" , (host >> 24) & BYTE, (host >> 16) & BYTE, (host >> 8) & BYTE, host & BYTE);
}

int main(){
    unsigned long ip = 0x10FF1112;
    unsigned char bitsNet = 23;
    hostIdentifier(ip, bitsNet);
    return 0;
}

