#include <pthread.h>
#include "run_flood_client.h"
#include "structures.h"
#include "flood_client.h"

int flood_client(run_mode_t rm){
  int i;
  int n =  rm.thread_amount;
  pthread_t thread[n];
  for ( i =0; i < n ; ++i ){
    pthread_create( &thread[i], NULL, run_flood_client, NULL);
    to_
  }

  for (i = 0; i < n; ++i )
    pthread_join ( thread[i], NULL );
  
  return 0;
}
