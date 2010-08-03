#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "socket_operations.h"
#include "flood_client.h"
#include "structures.h"
#include "client_threads.h"

void * run_flood_client ( void * arg ) {
  client_task_t * task = arg;
  pthread_t recv_thread;
  recv_flood_task_t recv_task;

  
  DEBUG_MSG("connecting to %s port %d\n", task -> ip_addr, task -> port );
 
  int sock = connect_to_server ( inet_addr ( task -> ip_addr ), htons ( task -> port ) );

  if ( -1 == sock ) {

    ERROR_MSG ( "failed to connect to server\n" );
    return NULL;
  }
  recv_task.sock = sock;
  recv_task.statistic_p = &task -> statistic;
  
  pthread_create ( &recv_thread, NULL, run_recv_flood_client, (void *) &recv_task );

  packet_t flood_packet;
  memset( &flood_packet, 0, sizeof ( flood_packet ) );

  for ( ; ; ) {
  
    //printf ( "1\n" );
  
    if ( -1 == send ( sock, &flood_packet, sizeof ( flood_packet ), 0) ) {
      ERROR_MSG( "send failed\n" );
      break;
    } else
      DEBUG_MSG ( "packet sent\n" );
      
      //printf ( "2\n" );
    }
     
     
    return NULL;    
 }

  
void * run_recv_flood_client ( void * arg ) {

  DEBUG_MSG ( "recv flood thread started\n" );

  recv_flood_task_t * task = arg;
  packet_t flood_packet;
  
  for ( ; ; )
    if ( sizeof ( flood_packet ) != recv_wrap ( task -> sock, &flood_packet ) ) {

      ERROR_MSG ( "recieving on sock %d failed\n", task -> sock );
      break;
    } else
      update_statistic ( task -> statistic_p );  

  return NULL;
}
