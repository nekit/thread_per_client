#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include "thread_statistics.h"
#include "structures.h"

void * get_statistics ( void * args ){

  INFO_MSG ( "statistic thread start\n" );

  statistic_task_t * task = args;
  struct timespec sleep_time;
  struct timespec remaning_sleep_time;

  sleep_time.tv_sec = task -> reporting_timeout / 1000;
  sleep_time.tv_nsec = (int)1E6 * (task -> reporting_timeout % 1000);  

  for ( ; ; ) {

    pthread_mutex_lock ( &task -> statistic_p -> mutex );

    printf( "%lld\n", task -> statistic_p -> counter );
    task -> statistic_p -> counter = 0;

    pthread_mutex_unlock ( &task -> statistic_p -> mutex );

    nanosleep ( &sleep_time, &remaning_sleep_time );
  }
  
  return NULL;
}
