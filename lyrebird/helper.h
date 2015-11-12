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

#define MAX_STATUS_LEN 12

#define ROUND_ROBIN "round robin"
#define FCFS "fcfs"


void myGetFileName(char* buffer_in, char* buffer_out, char* line);
int getStatus(char* status_char);
int myGetSchedule(FILE* file_p);
int fileEmpty(char* path);
char* getTime();
FILE* myFileOpen(char* filename, char* mode);
void myFileClose(FILE* file_p);
void myGetString(char* buffer, FILE* file_p, int length);
