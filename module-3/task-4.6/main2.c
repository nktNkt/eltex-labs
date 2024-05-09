#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define SEM_READ "/semread"

int main(int argc, char* argv[]) {
	int fd;

	sem_t* semRead;
	int value;

	semRead = sem_open(SEM_READ, O_EXCL);
	if (semRead == SEM_FAILED) {
		perror("sem_open:");
		exit(EXIT_FAILURE);
	}

	if (sem_trywait(semRead) == -1) {
		printf("Подключено максимальное число процессов.\n");
		exit(EXIT_FAILURE);
	}

	fd = open("numbers.txt", O_RDONLY);
	if (fd == -1) perror("File not opened");

	int readNum;
	while (read(fd, &readNum, sizeof(readNum)) > 0) {
		printf("%d ", readNum);
	}

	sem_getvalue(semRead, &value);
	printf("\nКол-во процессов, которые могут прочитать файл: %d\n", value);
	printf("Введите любую строку, чтобы выйти.\n");
	char buf[30];
	fgets(buf, 30, stdin);
	close(fd);
	sem_post(semRead);

	sem_close(semRead);
	exit(EXIT_SUCCESS);
}
