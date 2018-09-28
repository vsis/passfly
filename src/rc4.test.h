/*
 * Test rc4 implementation
 */

unsigned char expected_keystream(char * key, unsigned char key_length,
    unsigned char *keystream, unsigned char stream_length);

//Use test vectors from wikipedia (https://en.wikipedia.org/wiki/RC4)
void test_prnga_wiki(char * message);

//Use some test vector from RFC6229 (https://tools.ietf.org/html/rfc6229)
void test_prnga_rfc6229(char * message);
