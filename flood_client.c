#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "socket_operations.h"
#include "flood_client.h"
#include "structures.h"

void * run_flood_client (void * args ){

  struct timespec timeout;
  struct timespec left_time;
  client_task_t * client_task =  args;
  int sock = connect_to_server ( inet_addr(client_task -> ip_addr), htons(client_task -> port));
  packet_t packet;
  memset(packet, 0, sizeof(packet));

  for ( ;; ) {
    int len = send ( sock, packet , sizeof ( packet ), 0 );
    if ( -1 == len )
      break;
  
    nanosleep ( &timeout, &left_time );
    len = recv ( sock, packet , sizeof (packet ), 0 );
    if ( 0 == len )
      break;
    else{
      pthread_mutex_lock ( &client_task -> statistic.mutex );
      client_task -> statistic.counter++;
      pthread_mutex_unlock ( &client_task -> statistic.mutex );
    }
  }

    return NULL;
 }

  
