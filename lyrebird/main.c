#include "helper.h"
#include <unistd.h>
#include <fcntl.h>

const char end_token[4] = "end";
int main(int argc, char **argv) {
	pid_t pid;
	int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	char in_string[MAX_PATH] = { 0 };
	char out_string[MAX_PATH] = { 0 };

	int fd[num_cores - 1][2];
	int pd[num_cores-1][2];

	int string_status = 0;

	if (argc != 2) {
		printf("Usage: %s config_file.txt\n", argv[1]);
	}
	getTime();
	if (fileEmpty(argv[1])) {
		printf("[%s] The config file you specified is empty!!\n", getTime());
		exit(1);
	}
	int a;
	for (a = 0; a < num_cores - 1; a++) {
		pipe(pd[a]);
		pipe(fd[a]);
		pid = fork();
		if (pid < 0) {
			printf("[%s] Child creation failed. Process ID #%d\n", getTime(),
					getpid());
		} else if (pid == 0) {
			printf("[%s] Child ID #%d created\n", getTime(), getpid());
			int buf = a;
			close(fd[a][1]);
			close(pd[a][0]);
			char config_line[MAX_LENGTH + 1] = { 0 };
			int true = 1;
			while (true) {
				int write_r = write(pd[a][1], &buf, sizeof(buf));
				int read_r = read(fd[a][0], config_line, sizeof(config_line));
				if (strcmp(config_line, end_token) == 0) {
					break;
				}
				myGetFileName(in_string, out_string, config_line);
				printf("[%s] Child ID #%d to decrypt %s.\n", getTime(),
						getpid(), in_string);
				decryptor(in_string, out_string);
				printf("[%s] Decryption of %s complete.\n", getTime(),
						in_string, getpid());
			}

			close(fd[a][0]);
			printf("[%s] Child ID #%d exiting\n", getTime(), getpid());
			exit(0);
		}
	}
	int mode;
	int counter = 0;
	close(fd[a][0]);
	FILE* config_file = myFileOpen(argv[1], "r");
	char config_line[MAX_LENGTH + 1] = { 0 };
	while (feof(config_file) == 0) {
		if (feof(config_file) == 1) {
			break;
		}
		myGetString(config_line, config_file, 0);
		string_status = getStatus(config_line);
		if (string_status != 0) {
			mode = string_status;
		}
		if (string_status == 0 && mode == 1) {
			if (strcmp(config_line, "\n") == 0) {
				break;
			}
			int buf;
			int choose_child = counter % (num_cores - 1);
			read(pd[choose_child][0], &buf, sizeof(buf));
			write(fd[choose_child][1], config_line, sizeof(config_line));
			counter++;
		}
		if (string_status == 0 && mode == 2) {
			if (strcmp(config_line, "\n") == 0) {
				break;
			}
			int buf;
			int x;
			int read_r = 0;
			for (x = 0; x < num_cores - 1; x++){
				fcntl(pd[x][0], F_SETFL, O_NONBLOCK);
			}
			int true = 1;
			while (true) {
				x = x % (num_cores-1);
				close(pd[x][1]);
				if ((read_r = read(pd[x][0], &buf, sizeof(buf))) != -1) {
					write(fd[buf][1], config_line, sizeof(config_line));
					break;
				}else{
					x++;
				}
			}

		}
	}
	int z;
	for (z = 0; z < num_cores - 1; z++) {
		char end[4] = "end";
		int write_r = write(fd[z][1], end, sizeof(end));
	}
	fclose(config_file);
	int true = 1;
	while (true) {
		int status;
		pid_t pid = wait(&status);
		if (pid == -1) {
			if (errno == ECHILD) {
				printf(
						"[%s] All child processes terminated. Parent process ID #%d Exiting\n",
						getTime(), getpid());
				break;
			}
		} else {
			if (WIFEXITED(status)) {
				if (WEXITSTATUS(status) != 0) {
					printf(
							"[%s] Child process ID #%d did not terminate successfully.\n",
							getTime(), pid);
				}
			}
		}
	}
	int c;
	for (c = 0; c < num_cores - 1; c++) {
		close(fd[c]);
		close(pd[c]);
	}
}
