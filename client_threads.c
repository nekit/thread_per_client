#include "client_threads.h"
#include "structures.h"
#include "socket_operations.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>

inline void idx_to_packet ( uint32_t idx, packet_t * p ) {

  memcpy ( p, &idx, sizeof ( idx ) );
}

inline int value_of_packet ( packet_t * p ) {

  uint32_t val = -1;
  memcpy ( &val, p, sizeof ( val ) );
  return 0;
}

void init_sleep_time ( struct timespec * t,  int freq ) {

  t -> tv_nsec = (int) 1E9 / freq;
  t -> tv_sec = 0;
}


inline int update_statistic ( statistic_t * stat ) {

  pthread_mutex_lock ( &stat -> mutex );
  stat -> counter += 1;
  pthread_mutex_unlock ( &stat -> mutex );

  return 0;
}


// Какие то проблемы с if ( recv_idx != send_idx )

void * client ( void * arg ) {

  client_task_t * task = arg;

  DEBUG_MSG ( "thread starte \n" );
  
  int sock = connect_to_server ( inet_addr ( task -> ip_addr ), htons ( task -> port ) );

  if ( -1 == sock )
    return NULL;

  
   uint32_t send_idx = 28;
       printf ( "send before to pack: %d\n", send_idx  );

  uint32_t recv_idx;
  packet_t pack;
  int len;
  struct timespec sleep_time;
  struct timespec remaning_sleep_time;

  init_sleep_time ( &sleep_time, task -> frequency );
  

  return NULL;
}
