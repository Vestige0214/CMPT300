#include "decryptor.h"
#include <time.h>
#include "decrypt.h"
#include "memwatch.h"
#include "helper.h"
#include "helper.h"
#define MAX_LENGTH 1024

#define MAX_STR_LEN 165

int decryptor(char* in_path, char* out_path) {

	FILE* in_file = NULL;
	FILE* out_file = NULL;
	char in_string[MAX_STR_LEN] = { 0 };
	char out_string[MAX_STR_LEN] = { 0 };

	/* Open the encrypted file. Check return value. */
	in_file = myFileOpen(in_path, "r");

	/* Open the output file. Check return value. */
	out_file = myFileOpen(out_path, "w+");

	/* For each line in the encrypted file */
	while (feof(in_file) == 0) {

		/* Get encrypted string. */
		myGetString(in_string, in_file, MAX_STR_LEN);

		/* If at the end of the file, we get a null string.
		 Check for this. */
		if (strlen(in_string) == 0 && feof(in_file))
			break;

		/* Call the decryption algorithm */
		decrypt(in_string, out_string);

		/* Output the decrypted string. */
		fputs(out_string, out_file);
		fputc('\n', out_file);

		/* Reset output buffer for next string. */
		memset(out_string, 0, MAX_STR_LEN);

	}

	/* Close input and output files. */
	myFileClose(in_file);
	myFileClose(out_file);
	/* Exit. */
	return 0;

}

