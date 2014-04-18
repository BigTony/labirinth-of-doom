CC=g++
CFLAGS=-g -std=c++11 -pthread -Wall -pedantic -Iinc/
LIBS=-lboost_system -lboost_thread
SERVER_BIN=server
CLIENT_BIN=client
SERVER_SRC=server.cpp server.hpp server_connect.hpp server_connect.cpp message.cpp message.hpp maze.hpp maze.cpp
CLIENT_SRC=client.cpp client.hpp client_connect.hpp client_connect.cpp message.cpp message.hpp maze.hpp maze.cpp


all: server client


server: $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) $(LIBS) -o $(SERVER_BIN)


client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(LIBS) -o $(CLIENT_BIN)
	
	
clean:
	rm   *.o $(SERVER_BIN) $(CLIENT_BIN)
