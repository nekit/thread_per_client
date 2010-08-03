#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <memory.h>
#include <signal.h>
#include "structures.h"
#include "mega_log.h"
#include "run_server.h"
#include "socket_operations.h"

int  start_server(run_mode_t run_mode){
  printf("Server starts \n");
  pthread_t consumer [3000];
  struct pollfd pfd;
  int sock;
  signal (SIGPIPE,SIG_IGN);
  sock = bind_socket(inet_addr( run_mode.ip_addr), htons (run_mode.port), 5000);
  
  pfd.fd = sock;
  pfd.events = ( 0 | POLLIN );
  pfd.revents = 0;
  int i = 0;

  for(;;){
    poll ( &pfd, 1, -1);
    if ( (pfd.revents & POLLIN) != 0 ){
      int new_sock = accept( sock, NULL, NULL);
      if( -1 == new_sock )
	ERROR_MSG ( "accepting problem on socket : %d\n", sock );
      pthread_create ( &consumer[i], NULL, run, (void*) new_sock );
      printf ("new connection #%d\n", i);
	 pfd.revents = 0;
      i++;
      }
  }
  shutdown ( sock, SHUT_RDWR );
  return 0;
}
