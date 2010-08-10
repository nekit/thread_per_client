#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include "statistic.h"
#include "structures.h"

double diff_time(struct timeval * time1, struct timeval * time2){
  return (((double) time1 -> tv_sec - time2 -> tv_sec) + ((double)time1 -> tv_usec - time2 -> tv_usec)/1000000 );
}

void * statistics(void* arg){
  statistic_task_t * client = (void*) arg;
  struct timeval time1, time2;
  struct timespec sleep_time = { .tv_sec = 0, .tv_nsec = 900000000  };
  int count = 5;
  
  for( ;; ){
    gettimeofday(&time1, NULL);
    nanosleep(&sleep_time, NULL);
    pthread_mutex_lock(&client -> statistic_p -> mutex);
    gettimeofday(&time2, NULL);
    double time = diff_time (&time2, &time1);
    printf("statistics: %0.lf tps \n", (client -> statistic_p -> counter / time )  );
    if (0 == client -> statistic_p -> counter)
      if (0 == --count)
	return -1;
    
    client -> statistic_p -> counter = 0;
    pthread_mutex_unlock(&client -> statistic_p -> mutex);
  }
}
