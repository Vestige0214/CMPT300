#include <stdio.h>
#include <errno.h>

const int MAX_TWEET = 140;

int removeEndline(char * a, const int size);
int main(int argc, char **argv){
	if (argc == 3){
		char tweet[10][MAX_TWEET];
		int size_argv1 = 0;
		int size_argv2 = 0;
		while(argv[1][++size_argv1] != NULL);
		while (argv[2][++size_argv2] != NULL);
		FILE * inputFile = fopen(argv[1], "r");
		if (inputFile == NULL){
			perror("Error: ");
			exit(0);
		}
		char output[MAX_TWEET];
		fgets(output, MAX_TWEET, inputFile);
		removeEndline(output, MAX_TWEET);

		printf("Read strings %s\n", output);
	}
}

int removeEndline(char * a, const int size){
	int b;
	int newLineCaught = 0;
	for (b = 0; b < size; b++){
		if (a[b] == "'\'"){
			newLineCaught++;
		}
		if (a[b] == "'n'" && newLineCaught == 1){
			a[b-1] = "";
			a[b] = "";
		}
	}
}
//#include <stdio.h>
//
//
//void Decode(char *c, int *pointer);
//
//
//void Decode(char* c, int *pointer){
//	int a, b;
//	for (a = 7; a < *pointer; a+=8){
//		for (b = a; b < *pointer; b++){
//			printf("%c", c[b]);
//		}
//	}
//}

