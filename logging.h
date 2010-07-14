#ifndef LOGGING_H
#define LOGGING_H

typedef enum {

  LL_DEBUG,
  LL_INFO,
  LL_RELEASE,
  LL_LAST,
  
} log_level_t;

int to_log ( char * str, int log_level, int currenet_log_level );

#endif /* LOGGING_H */
