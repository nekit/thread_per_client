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

  to_log ( "thread started", LL_DEBUG, task -> log_level );
  
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
  
  for ( ; ; ) {

    idx_to_packet ( send_idx, &pack );

    //to_log ( "send packet", LL_DEBUG, task -> log_level );
    // printf ( "-> send: %d\n", send_idx  );
    
    len = send ( sock, &send_idx, sizeof ( send_idx ), 0 );
    if ( -1 == len )
      break;

    nanosleep ( &sleep_time, &remaning_sleep_time );
    
    int len_v = sizeof ( packet_t );
    packet_t packet;
    len = recv ( sock, &pack, sizeof ( pack ), 0 );
    printf("%d %d\n",len, value_of_packet( &pack ) );
    len = 0;
    int  i = 0, ll = 0;
    while ( len != len_v){
      ll = recv ( sock, &recv_idx, sizeof ( recv_idx ), 0 );
      len += ll;
      //      memcpy ( &recv_idx, &pack, sizeof ( recv_idx ) );
      //      idx_to_packet ( send_idx, &pack );
      printf("i : %d %d  %d\n", ++i, ll, recv_idx);
    }
    
    recv_idx = value_of_packet ( &pack );
    printf ( "-> send: %d recv: %d recv_len: %d\n", send_idx, recv_idx, len);

    if ( recv_idx != send_idx ) {
      to_log ( "ERROR!!! recv_idx != send_idx", LL_ERROR, task -> log_level );
      break;
    }
    printf("------> %d recv_idx %d\n", send_idx, recv_idx);
   
    to_log ( "packet recieved", LL_DEBUG, task -> log_level );

    send_idx += 1;
    update_statistic ( &task -> statistic );
  }

  return NULL;
}
