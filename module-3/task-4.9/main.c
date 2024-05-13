#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define SHM_NAME "/myshm"

int total = 0;
void* shmaddr = NULL;

void finishP(int sig) {
	printf("\nОбработанно данных: %d\n", total);
	munmap(shmaddr, 1024);
//	shm_unlink(SHM_NAME);
	exit(EXIT_SUCCESS);
}

void finishC(int sig) {
	munmap(shmaddr, 1024);
	exit(EXIT_SUCCESS);
}

int main() {
	srand(time(NULL));

	total = 0;
	pid_t pid;

	// Shared memory
	int shmid = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	if (shmid == -1) {
		perror("shm_open");
		exit(EXIT_FAILURE);
	}
	if (ftruncate(shmid, 1024) == -1) {
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}

	shmaddr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
	if (shmaddr == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	close(shmid);
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
