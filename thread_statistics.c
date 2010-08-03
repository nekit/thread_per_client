#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>
#include "thread_statistics.h"
#include "structures.h"

void * get_statistics ( void * args ){

  INFO_MSG ( "statistic thread start\n" );
  statistic_task_t * task = args;
  struct timespec sleep_time;
  struct timespec remaning_sleep_time;
  struct timeval last_time;
  struct timeval current_time;
  
  sleep_time.tv_sec = task -> reporting_timeout / 10000;
  sleep_time.tv_nsec = (int)1E6 * (task -> reporting_timeout % 1000);  
  gettimeofday (&last_time, NULL);
  
  for ( ;; ) {
    for( ;;){
       nanosleep ( &sleep_time, &remaning_sleep_time );
        gettimeofday (&current_time, NULL);
      if (current_time.tv_sec - last_time.tv_sec >= 1){
	break;
      }
    }
    
    pthread_mutex_lock ( &task -> statistic_p -> mutex );
    printf( "%lld\n", task -> statistic_p -> counter );

    if ( 0 == task -> statistic_p -> counter ) {
        ERROR_MSG ( "connection lost \n program exit\n" );
	exit ( EXIT_FAILURE );
    }
    
    task -> statistic_p -> counter = 0;
    pthread_mutex_unlock ( &task -> statistic_p -> mutex );
    last_time = current_time;
  }
  return NULL;
}
