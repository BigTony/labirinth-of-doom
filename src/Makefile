RM=rm
CC=g++
CFLAGS=-g -std=c++11 -pthread -Wall -pedantic -Iinc/
LIBS=-lboost_system
SERVER_BIN=server
SERVER_SRC=server.cpp server_connect.hpp server_connect.cpp
CLIENT_SRC=client.cpp client_connect.hpp client_connect.cpp
CLIENT_BIN=client

all: server client


server: $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) $(LIBS) -o $(SERVER_BIN)


client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(LIBS) -o $(CLIENT_BIN)
	
	
clean:
	$(RM)   *.o $(SERVER_BIN) $(CLIENT_BIN)
