#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>

static int waitvar = 2;

void blockaccess() {
	waitvar = 1;
//	printf("blockaccess\n");
}

void unlockaccess() {
	waitvar = 0;
//	printf("unlockaccess\n");
}

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int pipes[2];
	pid_t pid;
	int fd;
	fd = open("numbers.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1) printf("Error on create numbers.txt\n");

	int nums = 1;
	if (argc == 2) nums = atoi(argv[1]);

	if (pipe(pipes) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	signal(SIGUSR1, blockaccess);
	signal(SIGUSR2, unlockaccess);

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
			while (waitvar != 0);
			fd = open("numbers.txt", O_RDONLY);
			lseek(fd, -sizeof(buff), SEEK_END);	// 7. Чтение последнего числа из файла и вывод его на экран
			read(fd, &buff, sizeof(buff));
			close(fd);
			printf("%d\n", buff);
		}

		close(pipes[1]);
		exit(EXIT_SUCCESS);
	default:
		close(pipes[1]);

		int buf = -999999;

		while(read(pipes[0], &buf, sizeof(buf)) > 0) {
			kill(pid, SIGUSR1);				// 3. Остановка дочернего процесса
			fd = open("numbers.txt", O_WRONLY | O_APPEND);
			write(fd, &buf, sizeof(buf));			// 4. Запись числа в файл
			close(fd);
			sleep(1);					// 5. Ожидание 1 секунда
			kill(pid, SIGUSR2);				// 6. Возобновление дочернего процесса
		}

		wait(NULL);

		close(pipes[0]);
		exit(EXIT_SUCCESS);
	}

//	close(fd);
	exit(EXIT_SUCCESS);
}
