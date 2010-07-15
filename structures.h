#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdint.h>
#include <pthread.h>
#include "logging.h"

#define default_ip  "127.0.0.1"
#define default_port 1025
#define default_thread_amount 2
#define default_reporting_timeout 100
#define defualt_client_run_mode CM_CLIENT
#define default_frequency 100
#define default_log_level LL_DEBUG

#define IP_ADDRES_SIZE 20
#define PACKET_SIZE sizeof ( uint32_t )

typedef char packet_t[ PACKET_SIZE ];

typedef enum {

  CM_CLIENT,
  CM_FLOOD_CLIENT,
  CM_LAST,
  
} client_mode_t;

typedef struct run_mode_s {

  // enum value
  int client_run_mode;

  // amount of threads in client
  int thread_amount;

  // amont of transactions per second
  int frequency;

  // reporting timeout in milliseconds
  int reporting_timeout;

  int log_level;
  
  int port;

  char ip_addr[ IP_ADDRES_SIZE ];  
  
  
} run_mode_t;

typedef struct statistic_s {

  uint64_t counter;
  pthread_mutex_t mutex;
  
} statistic_t;

typedef struct client_task_s {

  int frequency;
  int port;
  int log_level;
  char ip_addr[ IP_ADDRES_SIZE ];
  statistic_t statistic;
    
} client_task_t; 

#endif
