#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int main(int argc, char* argv[]) {
	int fd;

	// Semaphores
	key_t key = ftok("./main.c", 1);
	int sem = semget(key, 2, 0666 | IPC_CREAT);
	struct sembuf lockFile = {0, -1, 0};
	struct sembuf unlockFile = {0, 1, 0};

	if (semctl(sem, 0, GETVAL) == 0) {
		printf("Подключено максимальное число процессов.\n");
		exit(EXIT_FAILURE);
	}

	semop(sem, &lockFile, 1);
	fd = open("numbers.txt", O_RDONLY);
	if (fd == -1) perror("File not opened");

	int readNum;
	while (read(fd, &readNum, sizeof(readNum)) > 0) {
		printf("%d ", readNum);
	}

	printf("\nКол-во процессов, которые могут прочитать файл: %d\n", semctl(sem, 0, GETVAL));
	printf("Введите любую строку, чтобы выйти.\n");
	char buf[30];
	fgets(buf, 30, stdin);
	close(fd);
	semop(sem, &unlockFile, 1);

	exit(EXIT_SUCCESS);
}
