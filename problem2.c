#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <semaphore.h>  

#define PARENT 0
#define CHILD 1
#define N 10000

sem_t sem; 
double min = 0; 

double shubert(double step, double x2);
void *runner(); 

int main(int argc, char *argv[]) {
	// create semaphore and initialize it to 1
	if(sem_init(&sem, 0, 1) < 0) { 
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		return -1;
	}

	pthread_t tid; 
	pthread_attr_t attr; 
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, NULL);

	double step = 0.5;
  double x1_start;
  double x1_stop; 
  double x1; 
  double x2; 
  double y;
	x1_start = step; 
  x1_stop = 2;

  //parent
	for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
		for (x2 = -2; x2 <= 2; x2 += step) {
			y = shubert(x1, x2);
			// acquire the semaphore
			sem_wait(&sem);
			// critical section
			if (y < min)
				min = y;
			// release semaphore 
			sem_post(&sem);
		}
	}
	
	pthread_join(tid, NULL);
	printf("min = %.2f ", min);
}

void *runner() {
	double step = 0.5; 
  double x1_start; 
  double x1_stop; 
  double x1; 
  double x2; 
  double y;
	x1_start = -2; 
  x1_stop = 0;

	for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
		for (x2 = -2; x2 <= 2; x2 += step) {
			y = shubert(x1, x2);
			// acquire the semaphore
			sem_wait(&sem);
			// critical section
			if (y < min)
				min = y;
			// release the semaphore
			sem_post(&sem);
		}
	}
	pthread_exit(0);
}

double shubert(double step, double x2) {
	double sum1 = 0; 
	double sum2 = 0;
	int i;
	for (i = 1; i <= 5; i++) {
		sum1 += i * cos((i + 1) * step + i);
		sum2 += i * cos((i + 1) * x2 + i);
	}
	return sum1 * sum2;
}

