CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJ = main.o client.o handler.o

all: tcp_post_client

tcp_post_client: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

main.o: main.c client.h handler.h
client.o: client.c client.h
handler.o: handler.c handler.h

clean:
	rm -f $(OBJ) tcp_post_client
