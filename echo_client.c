#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "parse_args.h"
#include "client.h"

int main ( int argc, char * argv[] ) {
  run_mode_t rm;
  if (1 == parse_args(argc, argv, &rm)){
    printf("parse argument exception");
    return (EXIT_FAILURE);
  }
  // 1 == rm.client_run_mode ? run_client(rm) : run_flood_client(rm);
  
  return (EXIT_SUCCESS);

}
