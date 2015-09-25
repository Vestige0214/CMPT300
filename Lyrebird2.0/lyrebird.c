#include <stdio.h>
#include <errno.h>

const int MAX_TWEET = 140;

int findEndline(char * a, const int size);
int main(int argc, char **argv){
	if (argc == 3){
		int a;
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
		char input[MAX_TWEET];
		int end_index;
		fgets(input, MAX_TWEET, inputFile);
		end_index = findEndLine(input, MAX_TWEET);

		char line[end_index];
		for (a = 0; a < end_index; a++){
			line[a] = input[a];
			printf("line %d is: %c\n", a, line[a]);
		}
		printf("Read strings %s\n", input);
	}
}

int findEndLine(char a[], const int size){
	int b;
	int newLineCaught = 0;
	for (b = 0; b < size; b++){
		if (a[b] == '\n'){
			return b;
		}
	}
}
void Decode(char *c, int *pointer);


void Decode(char* c, int *pointer){
	int a, b;
	for (a = 7; a < *pointer; a+=8){
		for (b = a; b < *pointer; b++){
			printf("%c", c[b]);
		}
	}
}

