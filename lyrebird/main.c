#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "decrypt.h"
#include "memwatch.h"
#include "decryptor.h"
#define MAX_LENGTH 2049
#define MAX_PATH 1024

#define MAX_STR_LEN 165

/*For getting the file paths in the config file
 *
 */
void myGetFileName(char* buffer_in, char* buffer_out, FILE* file_p) {
	memset(buffer_in, 0, MAX_PATH);
	memset(buffer_out, 0, MAX_PATH);
	fscanf(file_p, "%s %s", buffer_in, buffer_out);
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

int main (int argc, char **argv){
	pid_t pid;
	char in_string[MAX_PATH] = {0};
	char out_string[MAX_PATH] = {0};
	if (argc != 2){
		printf("Usage: %s config_file.txt\n", argv[1]);
	}
	getTime();
	if (fileEmpty(argv[1])){
		printf("[%s] The config file you specified is empty!!\n", getTime());
		exit(1);
	}
	FILE* config_file = myFileOpen(argv[1], "r");
	while (feof(config_file) == 0){
		if (feof(config_file) == 1){
			break;
		}
		myGetFileName(in_string, out_string, config_file);
		if (strlen (out_string) == 0 && strlen(in_string) == 0 && feof(config_file))
			break;
		pid = fork();
		if (pid < 0){
			printf("spawning failed\n");
		}else if (pid == 0){
			printf("[%s] Child ID #%d created to decrypt %s.\n", getTime(), getpid(), in_string);
			decryptor(in_string, out_string);
			printf("[%s] Decryption of %s complete. Process ID #%d Exiting.\n", getTime(), in_string, getpid());
			exit(0);
		}else{
			memset(out_string, 0, MAX_STR_LEN);
		}
	}
	fclose(config_file);
	int status;
	int i;
	int true = 1;
	while (true){
		int status;
		pid_t pid = wait(&status);
		if (pid == -1){
			if (errno == ECHILD){
				printf("[%s] All child processes terminated. Parent process ID #%d Exiting\n", getTime(), getpid());
				break;
			}
		}else{
			if (WIFEXITED(status)){
				if (WEXITSTATUS(status) != 0){
					printf("[%s] Child process ID #%d did not terminate successfully.\n", getTime(), pid);
				}
			}
		}
	}
}
