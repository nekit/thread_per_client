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
  
  rm -> client_run_mode = defualt_client_run_mode;
  rm -> frequency = default_frequency;
  rm -> thread_amount = default_thread_amount;
  rm -> reporting_timeout = default_reporting_timeout;
  strcpy(rm -> ip_addr , default_ip);
  rm -> port = default_port;
  rm -> log_level = default_log_level;
  
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
      if (0 <= atoi(optarg))
	rm -> frequency = atoi(optarg);
      else{
	printf("wrong frequency \n");
	return  1;
      }
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
      break;
    }
    case '?':{
      printf ( "reqiers arguments:\n -m: mode: 1-client  2-flood client\n -f: frequency\n -n: amount of threads\n -t: sleep time in milliseconds\n -s: ip-address\n -p: port\n");
      return 1;
    }
   }
  }
  return 0;
}
