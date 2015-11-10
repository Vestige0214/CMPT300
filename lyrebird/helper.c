#include "helper.h"


/*For getting the file paths in the config file
 *
 */
void myGetFileName(char* buffer_in, char* buffer_out, FILE* file_p) {
	memset(buffer_in, 0, MAX_PATH);
	memset(buffer_out, 0, MAX_PATH);
	fscanf(file_p, "%s %s", buffer_in, buffer_out);
}

int getStatus(char* status_char){
	if (memcmp(status_char, ROUND_ROBIN, sizeof(ROUND_ROBIN)) == 0){
		return 1;
	}else if (memcmp(status_char, FCFS, sizeof(FCFS)) == 0){
		return 2;
	}
}

int myGetSchedule(int* status, FILE* file_p){
	char status_char[MAX_STATUS_LEN];
	memset(status_char, 0, MAX_STATUS_LEN);
	fscanf(file_p, "%s", status_char);
	return getStatus(status_char);
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
