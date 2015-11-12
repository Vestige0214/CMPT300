#include "helper.h"

/* Wrapper for fgets that removes the extra newline character */
void myGetString(char* buffer, FILE* file_p, int length) {
	if (length == 0){
		length = MAX_LENGTH;
	}
	memset(buffer, 0, length);
	fgets(buffer, length, file_p);
	if (buffer[strlen(buffer) - 1] == '\n')
		buffer[strlen(buffer) - 1] = 0;
}

/*For getting the file paths in the config file
 *
 */
void myGetFileName(char* buffer_in, char* buffer_out, char* line) {
	memset(buffer_in, 0, MAX_PATH);
	memset(buffer_out, 0, MAX_PATH);
	sscanf(line, "%s %s", buffer_in, buffer_out);
}

int getStatus(char* status_char){
	char round[MAX_STATUS_LEN] = ROUND_ROBIN;
	char fcfs[MAX_STATUS_LEN] = FCFS;
	if (!memcmp(status_char, round, MAX_STATUS_LEN)){
		return 1;
	}else if (!memcmp(status_char, fcfs, MAX_STATUS_LEN)){
		return 2;
	}
	return 0;
}

/* Wrapper function for fopen that checks for errors and
 exits gracefully. */
FILE* myFileOpen(char* filename, char* mode) {

	FILE* file_p = fopen(filename, mode);
	if (!file_p) {
		printf("[%s] ERROR: Unable to open file %s\n", getTime(), filename);
		exit(13);
	}

	return file_p;

}

/* Wrapper function for fclose that checks for errors and
 exits gracefully. */
void myFileClose(FILE* file_p) {

	if (fclose(file_p) != 0) {
		printf("[%s] ERROR: Unable to close file!\n", getTime());
		exit(14);
	}

}

/*This function will read off the stat of the file and see
 * if it is empty
 */
int fileEmpty(char* path){
	struct stat st;
	stat(path, &st);
	if (st.st_size == 0){
		return 1;
	}else{
		return 0;
	}
}


/* Function for retrieving the current time of the system
 * and deleting the end line at the end
 */
char* getTime(){
	time_t t = time(NULL);
	struct tm *timeStruct;
	timeStruct = localtime(&t);
	char *DateTime = asctime(timeStruct);
	DateTime[strlen(DateTime) - 1] = 0;
	return DateTime;
}

int length(char* array){
	return (sizeof(array)/sizeof(array[0]));
}
