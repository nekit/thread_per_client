#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "parse_args.h"
#include "client.h"
#include "logging.h"

int main ( int argc, char * argv[] ) {
  
  run_mode_t rm;  
  if ( 0 != parse_args ( argc, argv, &rm ) ) {
    printf("parse argument exception");
    return (EXIT_FAILURE);
  }

  if ( CM_CLIENT == rm.client_run_mode )
    if ( 0 != run_client ( rm ) ) {

      to_log ( "client error", LL_ERROR, rm.log_level );
      return (EXIT_FAILURE);
    }
  
  return (EXIT_SUCCESS);
}
