#include <pthread.h>
#include "run_flood_client.h"
#include "structures.h"
#include "flood_client.h"
#include "mega_log.h"

int flood_client(run_mode_t rm){
  int i;
  int n =  rm.thread_amount;
  pthread_t thread[n];
  for ( i =0; i < n ; ++i ){
    pthread_create( &thread[i], NULL, run_flood_client, NULL);
    DEBUG_MSG (i + " thread created\n");
  }

  for (i = 0; i < n; ++i ){
    pthread_join ( thread[i], NULL );
    DEBUG_MSG (i + " thread joined\n");
  }
  
  return 0;
}
