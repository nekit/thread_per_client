#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include "run_flood_client.h"
#include "structures.h"
#include "flood_client.h"
#include "mega_log.h"
#include "thread_statistics.h"
#include <memory.h>
#include "statistic.h"
#include <unistd.h>
#include <sys/time.h>

int make_flood_task ( run_mode_t * rm, client_task_t * ct ) {

  memset ( ct, 0, sizeof (ct) );
  ct -> frequency = -1;
  ct -> port = rm -> port;
  memcpy( ct -> ip_addr, rm -> ip_addr, sizeof (rm -> ip_addr) );
  ct -> statistic.counter = 0;
  if ( 0 != pthread_mutex_init ( &ct -> statistic.mutex, NULL ) ) {
    DEBUG_MSG ( "Init statistic mutex problem\n");
    return 1;
  }
  return 0;
}

int flood_client ( run_mode_t rm ) {
  int i;
  pthread_t send_thread[rm.thread_amount];
  pthread_t statistic_thread;
  client_task_t flood_task;
  statistic_task_t statistic_task;
  struct timespec pause;
  struct timespec remaning;
  pause.tv_sec = 0;
  pause.tv_nsec = (int) 1E6;
  sem_init( &flood_task.semaphore, 0, 0);
  
  make_flood_task ( &rm, &flood_task );
  statistic_task.reporting_timeout = rm.reporting_timeout;
  statistic_task.statistic_p = &flood_task.statistic;
  //pthread_create ( &statistic_thread, NULL, get_statistics,  (void *) &statistic_task );
  pthread_create ( &statistic_thread, NULL, statistics,  (void *) &statistic_task );

  for ( i = 0; i < rm.thread_amount; ++i ){
    nanosleep ( &pause, &remaning );
    if ( 0 != pthread_create( &send_thread[i], NULL, run_flood_client, (void *) &flood_task) ) {
      ERROR_MSG ( "pthread_create failed create %d\n", i );
      perror ("pthread_create");
      return -1;
    }
    
  }
  sem_post( &flood_task.semaphore );
  for (i = 0; i < rm.thread_amount; ++i )
    pthread_join ( send_thread[i], NULL );

  pthread_join ( statistic_thread, NULL );
  return 0;
}
