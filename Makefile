echo_client := echo_client

echo_client_list := echo_client.o parse_args.o client.o client_threads.o socket_operations.o  flood_client.o thread_statistics.o flood_client.o run_flood_client.o mega_log.o

CFLAGS += -O2 -Wall
LDFLAGS += -lpthread

all: $(echo_client)

$(echo_client): $(echo_client_list)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) -c -MD $(CFLAGS) $<

include $(wildcard *.d)

clean:
	rm *.o *.d $(echo_client)