#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "rc4.h"
#include "rc4.test.h"

unsigned char expected_keystream(char * key, unsigned char key_length,
    unsigned char *keystream, unsigned char stream_length){

    struct rc4_status status;
    unsigned char index;
    strcpy(status.key, key);
    status.key_length = key_length;
    ksa(&status);
    for (index = 0; index < stream_length; index++){
        if (prnga(&status) != keystream[index]){
            return 0;
        }
    }
    return 1;
}

//Use test vectors from wikipedia (https://en.wikipedia.org/wiki/RC4)
void test_prnga_wiki(char * message){
    //test keys
    char vector_key[] = "Key";
    char vector_wiki[] = "Wiki";
    char vector_secret[] = "Secret";
    //expected keystreams
    unsigned char expected_key[10] = {0xeb, 0x9f, 0x77, 0x81, 0xb7, 0x34, 0xca,
        0x72, 0xa7, 0x19};
    unsigned char expected_wiki[6] = {0x60, 0x44, 0xdb, 0x6d, 0x41, 0xb7};
    unsigned char expected_secret[8] = {0x04, 0xd4, 0x6b, 0x05, 0x3c, 0xa8,
        0x7b, 0x59};
    //test produced keystream with expected keystreams
    if (! expected_keystream(vector_key, 3, expected_key, 10)){
        strcpy(message, "Key produced wrong keystream");
        return;
    }
    if (! expected_keystream(vector_wiki, 4, expected_wiki, 6)){
        strcpy(message, "Wiki produced wrong keystream");
        return;
    }
    if (! expected_keystream(vector_secret, 6, expected_secret, 8)){
        strcpy(message, "Secret produced wrong keystream");
    }
}

//Use some test vector from RFC6229 (https://tools.ietf.org/html/rfc6229)
void test_prnga_rfc6229(char * message){
    char key_40[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x00};
    char key_56[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00};
    unsigned char key_40_length = 5;
    unsigned char key_56_length = 7;
    unsigned char expected_40[16] = {0xb2, 0x39, 0x63, 0x05, 0xf0, 0x3d, 0xc0,
        0x27, 0xcc, 0xc3, 0x52, 0x4a, 0x0a, 0x11, 0x18, 0xa8};
    unsigned char expected_56[16] = {0x29, 0x3f, 0x02, 0xd4, 0x7f, 0x37, 0xc9,
        0xb6, 0x33, 0xf2, 0xaf, 0x52, 0x85, 0xfe, 0xb4, 0x6b};
    //compare produced keystreams with expected keystreams
    if (! expected_keystream(key_40, key_40_length, expected_40, 16)){
        strcpy(message, "40 bits key produced wrong keystream");
        return;
    }
    if (! expected_keystream(key_56, key_56_length, expected_56, 16)){
        strcpy(message, "56 bits key produced wrong keystream");
    }
}
