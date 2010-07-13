#ifndef SOCKET_OPERATIONS_H
#define SOCKET_OPERATIONS_H

#include <netinet/in.h>

#define handle_error(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int bind_socket ( uint32_t, uint16_t, int );
int connect_to_server ( uint32_t, uint16_t );
int send_wrap ( int, char [] );
int recv_wrap ( int, char ** );
int accept_wrap ( int );

#endif
