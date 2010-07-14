#include "client_threads.h"
#include "structures.h"
#include "socket_operations.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <memory.h>
#include <time.h>

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


void * client ( void * arg ) {

  client_task_t * task = arg;

  to_log ( "thread started", LL_DEBUG, task -> log_level );
  
  int sock = connect_to_server ( inet_addr ( task -> ip_addr ), htons ( task -> port ) );

  uint32_t send_idx = 0;
  uint32_t recv_idx;
  packet_t pack;
  int len;
  struct timespec sleep_time;
  struct timespec remaning_sleep_time;

  init_sleep_time ( &sleep_time, task -> frequency );

  for ( ; ; ) {

    idx_to_packet ( send_idx, &pack );
    len = send ( sock, &pack, sizeof ( pack ), 0 );
    if ( -1 == len )
      break;

    nanosleep ( &sleep_time, &remaning_sleep_time );

    len = recv ( sock, &pack, sizeof ( pack ), 0 );
    if ( 0 == len )
      break;

    recv_idx = value_of_packet ( &pack );

    if ( recv_idx != send_idx )
      break;

    send_idx += 1;
    update_statistic ( &task -> statistic );
  }

  return NULL;
}
