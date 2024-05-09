#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#define PNUM 3		// Максимальное число процессов, которые могут читать файл
#define SEM_READ "/semread"
#define SEM_WRITE "/semwrite"
#define SEM_NUM	"/semnum"

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
	sem_t* semRead;
	sem_t* semNum;
	sem_t* semWrite;

	//sem_unlink(SEM_READ);
	//sem_unlink(SEM_WRITE);
	//sem_unlink(SEM_NUM);

	semRead = sem_open(SEM_READ, O_CREAT, 0666, PNUM);
	semWrite = sem_open(SEM_WRITE, O_CREAT, 0666, 1);
	semNum = sem_open(SEM_NUM, O_CREAT, 0666, 0);

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
			sem_wait(semNum);			// 3. Ждать, пока родительский процесс не напишет число
			sem_wait(semRead);			// 8. Забрать доступ к файлу (чтение)
			fd = open("numbers.txt", O_RDONLY);
			lseek(fd, -sizeof(buff), SEEK_END);	// 9. Чтение последнего числа из файла и вывод его на экран
			read(fd, &buff, sizeof(buff));
			close(fd);
			sem_post(semRead);			// 10. Освободить доступ к файлу
			printf("%d\n", buff);
		}

		close(pipes[1]);
		exit(EXIT_SUCCESS);
	default:
		close(pipes[1]);

		int buf = -999999;
		int semReadVal;

		while(read(pipes[0], &buf, sizeof(buf)) > 0) {
			do { sem_getvalue(semRead, &semReadVal); }
			while (semReadVal != PNUM);
			sem_wait(semWrite);				// 4. Забрать доступ к файлу (запись)
			fd = open("numbers.txt", O_WRONLY | O_APPEND);
			write(fd, &buf, sizeof(buf));			// 5. Запись числа в файл
			close(fd);
			sem_post(semWrite);				// 6. Освободить доступ к файлу
			sem_post(semNum);				// 7. Передать дочернему процессу, что число записано

			sleep(1);
		}

		wait(NULL);

		close(pipes[0]);
		exit(EXIT_SUCCESS);
	}

	sem_close(semRead);
	sem_close(semWrite);
	sem_close(semNum);

	exit(EXIT_SUCCESS);
}
