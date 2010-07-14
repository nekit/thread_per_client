#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdint.h>

#define IP_ADDRES_SIZE 20
#define PACKET_SIZE sizeof ( uint32_t )
typedef char packet_t[ PACKET_SIZE ];

char default_ip[20];
#define default_ip  "92.168.1.1"
#define default_port 8080
#define default_thread_amount 10
#define default_reporting_timeout 100
#define defualt_client_run_mode 1
#define default_frequency 100

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
  
  int port;

  char ip_addr[ IP_ADDRES_SIZE ];  
  
  
} run_mode_t;

typedef struct client_task_s {

  int frequency;
  int reporting_timeout;  
  int port;
  char ip_addr[ IP_ADDRES_SIZE ];  
  
} client_task_t; 

#endif
