#include <pthread.h>
#include "run_flood_client.h"
#include "structures.h"
#include "flood_client.h"
#include "logging.h"

int flood_client(run_mode_t rm){
  int i;
  int n =  rm.thread_amount;
  pthread_t thread[n];
  for ( i =0; i < n ; ++i ){
    pthread_create( &thread[i], NULL, run_flood_client, NULL);
    to_log (i + " thread created", LL_DEBUG, rm.log_level);
  }

  for (i = 0; i < n; ++i ){
    pthread_join ( thread[i], NULL );
    to_log (i + " thread joined", LL_DEBUG, rm.log_level);
  }
  
  return 0;
}
