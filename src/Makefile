RM=rm
CC=g++
CFLAGS=-g -std=c++11 -Wall -pedantic
CLCFLAGS=-pthread
LIBS=-Llib/ -lboost_system
SERVER_BIN=server
SERVER_SRC=server.cpp
CLIENT_SRC=client.cpp
CLIENT_BIN=client

all: server client


server: $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) $(LIBS) -o $(SERVER_BIN)


client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLCFLAGS) $(CLIENT_SRC) $(LIBS) -o $(CLIENT_BIN)
	
	
clean:
	$(RM)   *.o
