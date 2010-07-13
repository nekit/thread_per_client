#include "socket_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>

void make_reusable ( int sock ) {

  // call before bind()
  
  int reuse_val = 1;
  if ( setsockopt ( sock, SOL_SOCKET, SO_REUSEADDR, &reuse_val, sizeof ( reuse_val ) ) == -1 )
    handle_error ( "reuse problem" );
}

int bind_socket ( uint32_t listn_ip, uint16_t port, int listn_backlog ) {

  int sock = socket ( PF_INET, SOCK_STREAM, 0 );
  if ( -1 == sock )
    handle_error ( "socket problem" );

  make_reusable ( sock );
  
  struct sockaddr_in serv_addr;
  memset ( &serv_addr, 0, sizeof ( struct sockaddr_in ) );
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = port;
  serv_addr.sin_addr.s_addr = listn_ip;

  if ( -1 == bind ( sock, (struct sockaddr *) &serv_addr, sizeof( struct sockaddr_in) ) )
    handle_error ( "bind problem" );

  if ( -1 == listen ( sock, listn_backlog ) )
    handle_error ( "listen backlog problem" );


#ifdef DEBUG
  printf ( "connection socket ready\n" );
#endif

  return sock;
}

int connect_to_server ( uint32_t server_ip, uint16_t port ) {

  struct sockaddr_in serv_addr;
  int sock = socket ( PF_INET, SOCK_STREAM, 0 );
  if ( -1 == sock )
    handle_error ( "socket problem" );

  memset ( &serv_addr, 0, sizeof ( struct sockaddr_in ) );
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = port;
  serv_addr.sin_addr.s_addr = server_ip;

#ifdef DEBUG
  printf ( "connecting to server..." );
#endif

  if ( connect ( sock, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in) ) == -1 )
    handle_error ( "connection to server failed" );

#ifdef DEBUG
  printf ( "connected successfully" );
#endif

  return sock;
}

int send_wrap ( int sock, char buf[] ) { 

  int buf_len = strlen ( buf ) + 1;
  int s_len;
  s_len = send ( sock, &buf_len, sizeof ( buf_len ), 0 );
  if ( -1 != s_len )
    s_len = send ( sock, buf, buf_len, 0 );

#ifdef DEBUG
  if ( s_len != -1 ) {
    printf ( "message send on socket %d\n", sock );
    printf ( "message :\n%s\n", buf );
  }  
#endif
  
  return s_len;
}

int recv_wrap ( int sock, char ** buf ) {

  int rcv_len;
  int buf_len;

  rcv_len = recv ( sock, &buf_len, sizeof ( buf_len ), 0 );
  if ( 0 == rcv_len )
    return rcv_len;

  *buf = malloc ( buf_len * sizeof ( char ) );
  rcv_len = recv ( sock, *buf, buf_len, 0 );

  if ( 0 == rcv_len ) {
    free ( *buf );
    *buf = NULL;
  }

#ifdef DEBUG
  if ( rcv_len != 0 )
    printf ( "recieved message:\n%s\n", *buf );
#endif

  return rcv_len;
}

int accept_wrap ( int sock ) {

  static struct sockaddr_in clnt_addr;
  static socklen_t sock_len;
  int new_sock;
  new_sock = accept ( sock, (struct sockaddr *) &clnt_addr, &sock_len);

  return new_sock;
}
