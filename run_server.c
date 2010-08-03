#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "structures.h"
#include "mega_log.h"
#include "client_threads.h"

void * run(void * args){
  TRACE_MSG ("run tpc server \n");
  int length;
  int  sock =  args;
  packet_t pack;
  while (1) {
    length = recv_wrap ( sock , &pack );
    if ( length <= 0 ) {
      ERROR_MSG ( "recieved failed on sock %d\n", sock );
      break;
    }
    length = send ( sock, &pack, sizeof ( pack ), 0 );
    if ( -1 == length ){
      ERROR_MSG ("sending error on socket: %d\n", sock);
      break;
    }
  }
  return NULL;
}
