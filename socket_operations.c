#include "socket_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include "logging.h"

#define SOCKET_OP_LOG_LEVEL 0

int make_reusable ( int sock ) {

  // call before bind()

   to_log ( "making socket reusable", LL_DEBUG, SOCKET_OP_LOG_LEVEL );
  
  int reuse_val = 1;
  if ( setsockopt ( sock, SOL_SOCKET, SO_REUSEADDR, &reuse_val, sizeof ( reuse_val ) ) == -1 ) {

    to_log ( "reuse problem", LL_ERROR, SOCKET_OP_LOG_LEVEL );
    return 1;
  }
  
  return 0;
}

int bind_socket ( uint32_t listn_ip, uint16_t port, int listn_backlog ) {

  to_log ( "binding socket", LL_DEBUG, SOCKET_OP_LOG_LEVEL );

  int sock = socket ( PF_INET, SOCK_STREAM, 0 );
  if ( -1 == sock ) {    

    to_log ( "socket problem", LL_ERROR, SOCKET_OP_LOG_LEVEL );
    return -1;
  }

  if ( 0 != make_reusable ( sock ) ){
    
    to_log ( "make reuse problem", LL_ERROR, SOCKET_OP_LOG_LEVEL );
    return -1;
  }
  
  struct sockaddr_in serv_addr;
  memset ( &serv_addr, 0, sizeof ( struct sockaddr_in ) );
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = port;
  serv_addr.sin_addr.s_addr = listn_ip;

  if ( -1 == bind ( sock, (struct sockaddr *) &serv_addr, sizeof( struct sockaddr_in) ) ) {

    to_log ( "bind problem", LL_ERROR, SOCKET_OP_LOG_LEVEL );
    return -1;
  }

  if ( -1 == listen ( sock, listn_backlog ) ) {
    
    to_log ( "listen problem", LL_ERROR, SOCKET_OP_LOG_LEVEL );
    return -1;
  }

  to_log ( "bind success", LL_DEBUG, SOCKET_OP_LOG_LEVEL );

  return sock;
}

int connect_to_server ( uint32_t server_ip, uint16_t port ) {

  to_log ( "connecting to server", LL_INFO, SOCKET_OP_LOG_LEVEL );

  struct sockaddr_in serv_addr;
  int sock = socket ( PF_INET, SOCK_STREAM, 0 );
  
  if ( -1 == sock ) {    

    to_log ( "socket problem", LL_ERROR, SOCKET_OP_LOG_LEVEL );
    return -1;
  }

  memset ( &serv_addr, 0, sizeof ( struct sockaddr_in ) );
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = port;
  serv_addr.sin_addr.s_addr = server_ip;

  if ( connect ( sock, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in) ) == -1 ) {

    to_log ( "connection to server failed", LL_ERROR, SOCKET_OP_LOG_LEVEL );
    return -1;
  }   

  to_log ( "connected successfully", LL_INFO, SOCKET_OP_LOG_LEVEL );
  
  return sock;
}

int accept_wrap ( int sock ) {

  // ???
  to_log ( "accepting", LL_DEBUG, SOCKET_OP_LOG_LEVEL );

  static struct sockaddr_in clnt_addr;
  static socklen_t sock_len;
  int new_sock;
  new_sock = accept ( sock, (struct sockaddr *) &clnt_addr, &sock_len);

  return new_sock;
}
