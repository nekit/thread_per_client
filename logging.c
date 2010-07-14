#include "logging.h"
#include <stdio.h>

int to_log ( char * str, int log_level, int currenet_log_level ) {

  if ( log_level >= currenet_log_level ) {

    fprintf ( stderr, "%s\n", str );
  }    

  return 0;
}
