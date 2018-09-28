#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "rc4.test.h"

unsigned char run_test(void (* test)(char* ), char * test_name){
    char message[128];
    strcpy(message, "");
    test(message);
    if (strcmp(message, "") != 0){
        printf("ERROR %s: %s\n", test_name, message);
        return 1;
    }
    return 0;
}
int main (int argc, char * argv[]){
    int failed_count = 0;
    //put here all tests
    failed_count += run_test(test_prnga_wiki, "test_prnga_wiki");
    failed_count += run_test(test_prnga_rfc6229, "test_prnga_rfc6229");

    return failed_count;
}
