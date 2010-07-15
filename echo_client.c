#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "structures.h"
#include "parse_args.h"
#include "client.h"
#include "mega_log.h"
#include "mega_log.h"

int main ( int argc, char * argv[] ) {

  signal ( SIGPIPE, SIG_IGN );
  
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
  
  return (EXIT_SUCCESS);
}
