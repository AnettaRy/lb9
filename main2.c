#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define A -2.0
#define B 2.0

pthread_new_thread_t new_thread;
double res = 0;
double h;

double Calc_X(double x){
	return pow(cos(x), 2) + pow(cos(x), 2);
}

void *Calc_I(void * arg){
	int i = *(int*) arg;	
	pthread_new_thread_lock(&new_thread);
	res += Calc_X(A + h*(i + 0.5));
	pthread_new_thread_unlock(&new_thread);
}

int main(int argc, char **argv){
	int p = 10;
	pthread_t *p_thread;
	if (argc > 1){
		p = atoi(argv[1]);
	}
	
	p_thread = malloc(sizeof(pthread_t) * p);
	pthread_new_thread_init(&new_thread, NULL);

	h = (B-A)/p;

	int i;
	for (i = 0; i < p; i++){
		if(pthread_create(&p_thread[i], NULL, &Calc_I, &i) !=0){
			fprintf(stderr, "Error (thread)\n");
			return 1;
		}		
	}

	for (i = 0; i < p; i++){
		if (pthread_join(p_thread[i], NULL) != 0) {
			printf("Error.\n");
			return 1;		
		}
	}

	printf("Значение интеграла: %f\n", res * h);

	pthread_new_thread_destroy(&new_thread);
	free(p_thread);
	return 0;
}

