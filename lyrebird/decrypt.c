#include "decrypt.h"

/* Decrypt the given string and return it in the given buffer. */
void decrypt(char* in_string, char* out_buffer) {
  
  char* tmp_string;
  unsigned long long cypher1, cypher2;
  int num_blocks = 0;
  int i;

  tmp_string = malloc((strlen(in_string) + 1) * sizeof(char));
  if (tmp_string == NULL) {
    fprintf(stderr, "ERROR: malloc failed!\n");
    exit(-13);
  }
  memset(tmp_string, 0, strlen(in_string) + 1);

  step1(in_string, tmp_string);

  num_blocks = strlen(tmp_string) / 6;

  for (i = 0; i < num_blocks; i++) {

    cypher1 = step2(tmp_string + i * BLOCK_SZ);
    cypher2 = step3(cypher1);
    step4(cypher2, out_buffer + i * BLOCK_SZ);

  }

  free(tmp_string);

} 

/* Remove every 8th character from the input string and return
   it in the given buffer */
void step1(char* in_string, char* out_buffer) {

  int i;

  for (i = 0; i < strlen(in_string); i++)
    if ( (i+1) % CHAR_SKIP )
      out_buffer[strlen(out_buffer)] = in_string[i];

}

/* Map 6-character string to base 41 number. */
unsigned long long step2(char* in_string) {

  /* Mapping between ASCII cypher text and base 41 numbers. */
  const char codeMap1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			   31, 0, 27, 37, 0, 39, 30, 33, 34, 
			   0, 0, 29, 35, 28, 38, 0, 0, 0, 0,
			   0, 0, 0, 0, 0, 0, 36, 0, 0, 0, 0, 
			   32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			   0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 0, 
			   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
			   12, 13, 14, 15, 16, 17, 18, 19, 20,
			   21, 22, 23, 24, 25, 26, 0, 0, 0, 0, 0};

  unsigned long long cypher = 0;
  int i;

  for (i = 0; i < BLOCK_SZ; i++)
    cypher += codeMap1[(int) in_string[i]] * (unsigned long long) 
      pow(CYPHER_BASE, BLOCK_SZ - i - 1);
  
  return cypher;

}

/* Use Montogomery's algorithm for RSA decryption */
unsigned long long step3(unsigned long long cypher) {

  /* Step 3's exponant and modulus */
  const unsigned long long N_mod = 4294434817;
  const unsigned long long D_exp = 1921821779;

  unsigned long long result;
  unsigned long long tmp_cypher;
  unsigned long long tmp_exp;
  
  result = 1; 
  tmp_cypher = cypher; 
  tmp_exp = D_exp;
  while (tmp_exp != 0) {
    if (tmp_exp & 1) {
      tmp_exp -= 1;
      result *= tmp_cypher;
      result %= N_mod;
    }
    else {
      tmp_exp /= 2;
      tmp_cypher *= tmp_cypher;
      tmp_cypher %= N_mod;
    }
  }
  
  return result;

}

/* Convert RSA decrypted number back into text */
void step4(unsigned long long cypher, char* out_buffer) {

  /* Mapping between base 41 numbers and ASCII characters. */
  const char codeMap2[] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
			   'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
			   'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
			   'x', 'y', 'z', '#', '.', ',', '\'', '!',
			   '?', '(', ')', '-', ':', '$', '/', '&',
			   '\\'};

  int i;
  unsigned int tmp_char;

  for(i = BLOCK_SZ - 1; i >= 0; i--) {
    tmp_char = cypher % CYPHER_BASE;
    cypher = (cypher - tmp_char) / CYPHER_BASE;
    out_buffer[i] = codeMap2[tmp_char];
  }

}
