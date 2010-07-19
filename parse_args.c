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
  [CM_SERVER] = "server",
};

int parse_args ( int argc, char * argv[], run_mode_t * rm ) {
  
  rm -> client_run_mode = defualt_client_run_mode;
  rm -> frequency = default_frequency;
  rm -> thread_amount = default_thread_amount;
  rm -> reporting_timeout = default_reporting_timeout;
  strcpy(rm -> ip_addr , default_ip);
  rm -> port = default_port;
  
  int res = 0;
  
  while ( (res = getopt(argc,argv,"m:f:n:t:s:p:h:L:")) != -1) {
    switch (res){
    case 'm': {
      TRACE_MSG ( "optarg: %s\n", optarg );
      TRACE_MSG ( "rm_n[1]: %s\n", rm_names[1] );
      int i;
      for (i = 0; i < sizeof (rm_names) / sizeof (rm_names[0]); ++i){
	if (rm_names[i] != 0)
	  if ( 0 == strcasecmp (optarg, rm_names[i])){
	    rm -> client_run_mode = i;
	    break;
	  }
      }
      if (i >= sizeof (rm_names) / sizeof (rm_names[0]))
	rm -> client_run_mode = CM_CLIENT;
      
      DEBUG_MSG (" parse mode done ");
      break;
    }
    case 'f': {
      if (0 <= atoi(optarg))
	rm -> frequency = atoi(optarg);
      else{
	printf("wrong frequency \n");
	return  1;
      }
      DEBUG_MSG (" parse frequency done \n");
      break;
    }
    case 'n':{
      if (0 <  atoi(optarg)){
	rm -> thread_amount = atoi(optarg);
	//	printf("%d \n", rm -> thread_amount);
      }
      else{
	printf("wrong thread amount \n");
	return  1;
      }
      DEBUG_MSG (" parse thread amount done \n");
      break;
    }
    case 't':{
      if (0 <= atoi(optarg) ){
	rm -> reporting_timeout = atoi(optarg);
	//	printf("%d \n", rm -> reporting_timeout);
      }
      else{
	printf("wrong timeout \n");
	return 1;
      }
      break;
    }
    case 's':{
      stpcpy(rm -> ip_addr, optarg);
      printf("%s \n", rm -> ip_addr);
        break;
    }
    case 'p':{
      if (0 < atoi(optarg))
	rm -> port = atoi(optarg);
      else{
	printf("wrong port \n");
	return 1;
      }
      DEBUG_MSG (" parse ip done" );
      break;
    }
    case 'h':{
      printf ( "reqiers arguments:\n -m: mode: 1-client  2-flood client\n -f: frequency\n -n: amount of threads\n -t: sleep time in milliseconds\n -s: ip-address\n -p: port\n");
      return 1;
    }
    case 'L' :
      TRACE_MSG( "parsing level %s\n", optarg );
      INIT_LOG_LEVEL( optarg );
      break;
    }
  }
  return 0;
}
