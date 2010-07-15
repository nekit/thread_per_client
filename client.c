#include "client.h"
#include "client_threads.h"
#include <pthread.h>
#include <memory.h>
#include "mega_log.h"
#include "client_threads.h"
#include "mega_log.h"

int make_client_task ( run_mode_t * rm, client_task_t * ct ) {

  memset ( ct, 0, sizeof (ct) );
  ct -> frequency = rm -> frequency;
  ct -> port = rm -> port;
   memcpy( ct -> ip_addr, rm -> ip_addr, sizeof (rm -> ip_addr) );

  ct -> statistic.counter = 0;
  if ( 0 != pthread_mutex_init ( &ct -> statistic.mutex, NULL ) ) {

    DEBUG_MSG ( "Init statistic mutex problem\n");
    return 1;
  }

  return 0;
}

int run_client ( run_mode_t run_mode ) {

  INFO_MSG ( "Client starting %d\n", 1 );

  pthread_t thread[run_mode.thread_amount];
  client_task_t client_task;
  if ( 0 != make_client_task ( &run_mode, &client_task ) ) {

    DEBUG_MSG ( "make_client_task error\n" );
    return 1;
  }

  int i;
  for ( i = 0; i < run_mode.thread_amount; ++i )
    if ( 0 != pthread_create( &thread[i], NULL, client, (void *) &client_task ) ) {

      DEBUG_MSG ( "thread create problem\n");
      return 1;
    }

  for ( i = 0; i < run_mode.thread_amount; ++i )
    pthread_join ( thread[i], NULL );

  DEBUG_MSG ( "client finish\n" );

  return 0;
}
