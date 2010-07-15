#ifndef CLIENT_THREADS_H
#define CLIENT_THREADS_H

#include "structures.h"

void * client ( void * );

int recv_wrap ( int sock, packet_t * pack_p  );
inline int update_statistic ( statistic_t * stat );

#endif /* End of CLIENT_THREADS_H */
