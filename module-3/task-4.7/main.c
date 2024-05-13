#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>

int total = 0;
void* shmaddr = NULL;

void finishP(int sig) {
	printf("\nОбработанно данных: %d\n", total);
	shmdt(shmaddr);
	exit(EXIT_SUCCESS);
}

void finishC(int sig) {
	shmdt(shmaddr);
	exit(EXIT_SUCCESS);
}

int main() {
	srand(time(NULL));

	total = 0;
	pid_t pid;

	// Shared memory
	key_t key = ftok("./main.c", 1);
	int shmid = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0666);
	if (shmid == -1) shmid = shmget(key, 1, 0666);

	shmaddr = shmat(shmid, NULL, 0);
	if (shmaddr == (void*)-1) {
		perror("shmat");
		exit(EXIT_FAILURE);
	}

	int* nums = (int*)shmaddr;

	// Здесь nums[0] выполняет роль переключателя.
	// nums[0] == -1 - Родительский процесс генерирует числа,
	//   и при окончании в nums[0] будет записано их кол-во N.
	// nums[0] == N - Дочерний процесс ищет макс/мин числа,
	//   и при окончании в nums[0] будет записано -1.
	nums[0] = -1;

	switch (pid = fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		signal(SIGINT, finishC);
		int nmax, nmin, nn;
		while(1) {
			while(nums[0] == -1);	// Ожидание записи чисел
			nn = nums[0];
			nmax = nums[1];
			nmin = nums[1];
			for (int i = 2; i < nn + 1; i++) {
				if (nums[i] > nmax) nmax = nums[i];
				if (nums[i] < nmin) nmin = nums[i];
			}
			// Запись макс/мин чисел в разделяемую память
			nums[0] = -1;
			nums[1] = nmax;
			nums[2] = nmin;
		}
	default:
		signal(SIGINT, finishP);
		int x = 0;
		while (1) {
			// Генерация чисел в разделяемую память
			x = rand() % 100 + 1;
			for (int i = 1; i < x + 1; i++) {
				nums[i] = rand() % 10000 + 1;
			}
			nums[0] = x;  // записываем число случайных чисел
			while(nums[0] != -1);

			// Получение макс/мин чисел и вывод
			printf("Genereated numbers: %d\tMax: %d\tMin: %d\n", x, nums[1], nums[2]);
			total++;
		}
	}
}
