#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "structures.h"
#include "parse_args.h"
#include "client.h"
#include "mega_log.h"
#include "mega_log.h"
#include "run_flood_client.h"
#include "start_tpc_server.h"

int main ( int argc, char * argv[] ) {

   signal ( SIGPIPE, SIG_IGN );
  INIT_LOG_LEVEL ("INFO");
  run_mode_t rm;  
  if ( 0 != parse_args ( argc, argv, &rm ) ) {
    printf("parse argument exception \n");
    return (EXIT_FAILURE);
  }


  if ( CM_CLIENT == rm.client_run_mode )
    if ( 0 != run_client ( rm ) ) {

      DEBUG_MSG ( "client error\n");
      return (EXIT_FAILURE);
    }

  if ( CM_FLOOD_CLIENT == rm.client_run_mode )
    if ( 0 != flood_client ( rm ) ) {

      DEBUG_MSG ( "flood client error\n");
      return (EXIT_FAILURE);
    }
  if ( CM_SERVER == rm.client_run_mode )
    if ( 0 !=   start_server(rm) ) {
      DEBUG_MSG ( "server error\n");
      return (EXIT_FAILURE);
    }
  
  return (EXIT_SUCCESS);
}
