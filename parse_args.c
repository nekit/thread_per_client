#include <memory.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "parse_args.h"

static char * rm_names[] = {
  [CM_CLIENT] = "client",
  [CM_FLOOD_CLIENT] = "flood_client",
};

int parse_args ( int argc, char * argv[], run_mode_t * rm ) {
  
  /* rm -> client_run_mode = defualt_client_run_mode;
  rm -> frequency = default_frequency;
  rm -> thread_amount = default_thread_amount;
  rm -> reporting_timeout = default_reporting_timeout;
  //  rm -> ip_addr = default_ip;
  strcpy ( rm -> ip_addr, default_ip );
  rm -> port = default_port;
  int res = 0;
  
  while ( (res = getopt(argc,argv,"m:f:n:t:s:p:")) != -1) {
    switch (res){
    case 'm': {
      int i;
      for (i = 0; i < sizeof (rm_names) / sizeof (rm_names[0]); ++i)
	if (rm_names[i] != 0)
	  if (strcasecmp (optarg, rm_names[i]))
	    break;
      if (i >= sizeof (rm_names) / sizeof (rm_names[0]))
	rm -> client_run_mode = CM_CLIENT;
      break;
    }
    case 'f': {
      int i;
      for (i = 0; i < sizeof (rm_names) / sizeof (rm_names[0]); ++i)
	if (rm_names[i] != 0)
	  if (strcasecmp (optarg, rm_names[i]))
	    break;
      if (i >= sizeof (rm_names) / sizeof (rm_names[0]))
	rm -> frequency = CM_CLIENT;
      break;
    }
    case 'n':{
      int i;
     for (i = 0; i < sizeof (rm_names) / sizeof (rm_names[0]); ++i)
	if (rm_names[i] != 0)
	  if (strcasecmp (optarg, rm_names[i]))
	    break;
      if (i >= sizeof (rm_names) / sizeof (rm_names[0]))
	rm -> thread_amount = CM_CLIENT;
      break;
    }
    case 't':{
      int i;
      for (i = 0; i < sizeof (rm_names) / sizeof (rm_names[0]); ++i)
	if (rm_names[i] != 0)
	  if (strcasecmp (optarg, rm_names[i]))
	    break;
      if (i >= sizeof (rm_names) / sizeof (rm_names[0]))
	rm -> reporting_timeout = CM_CLIENT;
      else{
	printf("wrong parametr \n");
	return 1;
      }
      break;
    }
    case 's':{
      int i;
       for (i = 0; i < sizeof (rm_names) / sizeof (rm_names[0]); ++i)
	if (rm_names[i] != 0)
	  if (strcasecmp (optarg, rm_names[i]))
	    break;
      if (i >= sizeof (rm_names) / sizeof (rm_names[0]))
	strcpy (rm -> ip_addr, CM_CLIENT);
        break;
    }
    case 'p':{
      int i;
      for (i = 0; i < sizeof (rm_names) / sizeof (rm_names[0]); ++i)
	if (rm_names[i] != 0)
	  if (strcasecmp (optarg, rm_names[i]))
	    break;
      if (i >= sizeof (rm_names) / sizeof (rm_names[0]))
	rm -> port = CM_CLIENT;
    
      else{
	printf("wrong parametr \n");
	return 1;
      }
      break;
    }
    case '?':{
      printf ( "reqiers arguments:\n -m: mode: 1-client  2-flood client\n -f: frequency\n -n: amount of threads\n -t: sleep time in milliseconds\n -s: ip-address\n -p: port\n");
      return 1;
    }
   }
  }

  */
  return 0;
}
