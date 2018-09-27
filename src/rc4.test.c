#include "rc4.h"

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
void test_prnga(char * message){
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
    //test produced keystream with spected keystreams
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
