#include "client.h"
#include "client_threads.h"
#include <pthread.h>
#include <memory.h>

int make_client_task ( run_mode_t * rm, client_task_t * ct ) {

  memset ( ct, 0, sizeof (ct) );
  ct -> frequency = rm -> frequency;
  ct -> port = rm -> port;
  memcpy( ct -> ip_addr, rm -> ip_addr, sizeof (rm -> ip_addr) );

  return 0;
}

int run_client ( run_mode_t run_mode ) {

  /*pthread_t thread[run_mode.thread_amount];
  client_task_t client_task;
  make_client_task ( &run_mode, &client_task );
  */


  return 0;
}
