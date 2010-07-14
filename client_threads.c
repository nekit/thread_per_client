#include "client_threads.h"
#include "structures.h"
#include "socket_operations.h"
#include <stdlib.h>
#include <arpa/inet.h>

void * client ( void * arg ) {

  client_task_t * task = arg;
  int sock = connect_to_server ( inet_addr ( task -> ip_addr ), htons ( task -> port ) );

  int timeout = 0;
  uint32_t send_idx = 0;
  //  packet_t send_packet;
  uint32_t recv_idx;
  
  int len;

  for ( ; ; ) {

    len = send ( sock, &send_idx, sizeof ( send_idx ), 0 );
    if ( -1 == len )
      break;

    // sleep ( timeout );


    len = recv ( sock, &recv_idx, sizeof ( recv_idx ), 0 );
    if ( 0 == len )
      break;

    if ( recv_idx != send_idx )
      break;

    send_idx += 1;    
  }


  return NULL;
}
