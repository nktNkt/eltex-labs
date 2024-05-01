#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int pipes[2];
	pid_t pid;
	int fd;
	fd = open("numbers.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1) printf("Error on create numbers.txt\n");

	int nums = 1;
	if (argc == 2) nums = atoi(argv[1]);

	// Semaphores
	key_t key = ftok("./main.c", 1);
	int sem = semget(key, 2, 0666 | IPC_CREAT);
	struct sembuf lockFile[2] = {{0, 0, 0}, {0, 1, 0}};
	struct sembuf unlockFile = {0, -1, 0};
	struct sembuf writeNum = {1, 1, 0};
	struct sembuf readNum = {1, -1, 0};

	union semun arg;
	arg.val = 0;
	semctl(sem, 0, SETVAL, arg);
	arg.val = 0;
	semctl(sem, 1, SETVAL, arg);

	if (pipe(pipes) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	switch (pid = fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		close(pipes[0]);

		int buff = -999999;
		int k;

		for (int i = 0, n = -999999; i < nums; i++) {
			n = rand() % 10000 - 5000;		// 1. Дочерний процесс генерирует случайные числа
			write(pipes[1], &n, sizeof(n));		// 2. Передача числа родительскому процессу
			semop(sem, &readNum, 1);		// 3. Ждать, пока родительский процесс не напишет число
			semop(sem, lockFile, 2);		// 8. Забрать доступ к файлу
			fd = open("numbers.txt", O_RDONLY);
			lseek(fd, -sizeof(buff), SEEK_END);	// 9. Чтение последнего числа из файла и вывод его на экран
			read(fd, &buff, sizeof(buff));
			close(fd);
			semop(sem, &unlockFile, 1);		// 10. Освободить доступ к файлу
			printf("%d\n", buff);
		}

		close(pipes[1]);
		exit(EXIT_SUCCESS);
	default:
		close(pipes[1]);

		int buf = -999999;

		while(read(pipes[0], &buf, sizeof(buf)) > 0) {
			semop(sem, lockFile, 2);			// 4. Забрать доступ к файлу
			fd = open("numbers.txt", O_WRONLY | O_APPEND);
			write(fd, &buf, sizeof(buf));			// 5. Запись числа в файл
			close(fd);
			semop(sem, &unlockFile, 1);			// 6. Освободить доступ к файлу
			semop(sem, &writeNum, 1);			// 7. Передать дочернему процессу, что число записано
		}

		wait(NULL);

		semctl(sem, 0, IPC_RMID);
		close(pipes[0]);
		exit(EXIT_SUCCESS);
	}

	exit(EXIT_SUCCESS);
}
