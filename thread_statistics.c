#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include "thread_statistics.h"
#include "structures.h"

void * get_statistics ( void * args ){
  client_task_t * client_task = args;
  struct timespec timeout;
  struct timespec timeleft;
  for ( ;; ){
    nanosleep ( &timeout,  &timeleft);
    to_log (" try to lock and get statistics ", LL_DEBUG, client_task -> log_level);
    pthread_mutex_lock ( &client_task -> statistic.mutex);
    to_log (" locked and got statistics ", LL_DEBUG, client_task -> log_level);
    printf("current thread client statistics: %0* \n", client_task -> statistic.counter);
    pthread_mutex_unlock ( &client_task -> statistic.mutex);
  }
  return NULL;
}
