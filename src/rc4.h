/*
 * Definition of RC4 algorithm
 */

//status of an arcfour instance
struct rc4_status {
  unsigned char i;
  unsigned char j;
  char key[256];
  unsigned char key_length;
  unsigned char s[256];
};

void swap(struct rc4_status * status);

//key scheduling algorithm
void ksa(struct rc4_status * status);

//pseudo-random number generation algorithm
unsigned char prnga(struct rc4_status * status);
