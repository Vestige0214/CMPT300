#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "decrypt.h"
#include "memwatch.h"
#include "helper.h"
#include "decryptor.h"
#define MAX_LENGTH 2049
#define MAX_PATH 1024

#define MAX_STR_LEN 165

#define MAX_STATUS_LEN 15

#define ROUND_ROBIN "round robin"
#define FCFS "fcfs"



int main (int argc, char **argv){
	pid_t pid;

	char in_string[MAX_PATH] = {0};
	char out_string[MAX_PATH] = {0};

	int mode = 0;

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
		while (mode == 0){
			mode = myGetSchedule(mode, config_file);
		}
		printf("what is mode right now? %d\n" mode);
//		myGetFileName(in_string, out_string, config_file);
//		if (strlen (out_string) == 0 && strlen(in_string) == 0 && feof(config_file))
//			break;
//		pid = fork();
//		if (pid < 0){
//			printf("spawning failed\n");
//		}else if (pid == 0){
//			printf("[%s] Child ID #%d created to decrypt %s.\n", getTime(), getpid(), in_string);
//			decryptor(in_string, out_string);
//			printf("[%s] Decryption of %s complete. Process ID #%d Exiting.\n", getTime(), in_string, getpid());
//			exit(0);
//		}else{
//			memset(out_string, 0, MAX_STR_LEN);
//		}
	}
//	fclose(config_file);
//	int status;
//	int i;
//	int true = 1;
//	while (true){
//		int status;
//		pid_t pid = wait(&status);
//		if (pid == -1){
//			if (errno == ECHILD){
//				printf("[%s] All child processes terminated. Parent process ID #%d Exiting\n", getTime(), getpid());
//				break;
//			}
//		}else{
//			if (WIFEXITED(status)){
//				if (WEXITSTATUS(status) != 0){
//					printf("[%s] Child process ID #%d did not terminate successfully.\n", getTime(), pid);
//				}
//			}
//		}
//	}
}
