
#ifndef _DECRYPT_H_
#define _DECRYPT_H_

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BLOCK_SZ 6
#define CYPHER_BASE 41
#define CHAR_SKIP 8

void decrypt(char* in_string, char* out_buffer);
void step1(char* in_string, char* out_buffer);
unsigned long long step2(char* in_string);
unsigned long long step3(unsigned long long cypher);
void step4(unsigned long long cypher, char* out_buffer);

#endif 

