#include "client_threads.h"
#include "structures.h"
#include "socket_operations.h"
#include "mega_log.h"
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
  return val;
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


int recv_wrap ( int sock, packet_t * pack_p  ) {

  TRACE_MSG ( "recieving packet on sock %d\n", sock );

  int rcv_len = 0;
  int len;

  while ( rcv_len != sizeof ( *pack_p ) ) {

    len = recv ( sock, pack_p + rcv_len, sizeof ( *pack_p ) - rcv_len, 0 );

    TRACE_MSG( "recieved temproary len = %d\n", len );
    
    if ( len < 0 ) {

      ERROR_MSG("recieve failed on sock %d\n", sock );
      return -1;
    }

    rcv_len += len;
  }

  TRACE_MSG ( "packet recived on sock %d len %d\n", sock, rcv_len );

  return rcv_len;
}

void * client ( void * arg ) {

  client_task_t * task = arg;

  DEBUG_MSG("connecting to %s port %d\n", task -> ip_addr, task -> port );
  DEBUG_MSG ( "thread start \n" );
  
  int sock = connect_to_server ( inet_addr ( task -> ip_addr ), htons ( task -> port ) );

  if ( -1 == sock ) {

    ERROR_MSG ( "connection to server failed\n" );
    return NULL;
  }

  
  uint32_t send_idx = 1;
  TRACE_MSG ( "initial send_idx: %d\n", send_idx );
  uint32_t recv_idx;
  packet_t pack;
  int len;
  struct timespec sleep_time;
  struct timespec remaning_sleep_time;

  init_sleep_time ( &sleep_time, task -> frequency );

  for ( ; ; ) {

    TRACE_MSG ( "working\n" );

    idx_to_packet ( send_idx, &pack );

    TRACE_MSG( "sending idx %d on sock %d\n", send_idx, sock );
    
    len = send ( sock, &pack, sizeof ( pack ), 0 );
    if ( -1 == len )
      break;

    TRACE_MSG( "idx %d sent on sock %d\n", send_idx, sock );

    nanosleep ( &sleep_time, &remaning_sleep_time );
   
    len = recv_wrap ( sock, &pack );
    if ( len < 0 ) {

      ERROR_MSG ( "recieved failed on sock %d\n  idx = %d\n", sock, send_idx );
      perror ("!!!!");
      break;
    }
    
    recv_idx = value_of_packet ( &pack );

    DEBUG_MSG ( "sock %d recv_idx %d\n", sock, recv_idx );

    if ( recv_idx != send_idx ) {

      ERROR_MSG ( "recv_idx != send_idx\n send_idx: %d\n recv_idx: %d\n", send_idx, recv_idx );     
      break;
    }

    send_idx += 1;
    update_statistic ( &task -> statistic );
  }

  INFO_MSG ( "client off\n" );

  return NULL;
}
