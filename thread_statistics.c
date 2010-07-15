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
    DEBUG_MSG ("statictic thread sleep \n");
    pthread_mutex_lock ( &client_task -> statistic.mutex);
    DEBUG_MSG (" got statistics \n");
    printf("current thread client statistics: %0* \n", client_task -> statistic.counter);
    pthread_mutex_unlock ( &client_task -> statistic.mutex);
  }
  return NULL;
}
