/*
 * Definition of RC4 algorithm
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rc4.h"

void swap(struct rc4_status * status){
    unsigned char tmp;
    tmp = status->s[status->i];
    status->s[status->i] = status->s[status->j];
    status->s[status->j] = tmp;
}

//key scheduling algorithm
void ksa(struct rc4_status * status){
    status->i = 0;
    status->j = 0;
    do{
        status->s[status->i] = status->i;
        status->i++;
    }while(status->i);
    //use key to generate a pseudorandom s
    do{
        status->j += status->key[status->i % status->key_length]
            + status->s[status->i];
        swap(status);
        status->i++;
    }while(status->i);
    //reset j
    status->j = 0;
}

//pseudo-random number generation algorithm
unsigned char prnga(struct rc4_status * status){
    unsigned char s_index;
    status->i++;
    status->j += status->s[status->i];
    swap(status);
    s_index = status->s[status->i] + status->s[status->j];
    return status->s[s_index];
}
