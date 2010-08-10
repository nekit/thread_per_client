tpc_start := tpc_start

tpc_start_list := tpc_start.o parse_args.o client.o client_threads.o socket_operations.o  flood_client.o thread_statistics.o flood_client.o run_flood_client.o mega_log.o start_tpc_server.o run_server.o statistic.o

CFLAGS += -O2 -Wall
LDFLAGS += -lpthread

all: $(tpc_start)

$(tpc_start): $(tpc_start_list)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) -c -MD $(CFLAGS) $<

include $(wildcard *.d)

clean:
	rm *.o *.d $(tpc_start)