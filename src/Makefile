CC=g++
CFLAGS=-g -std=c++11 -pthread -Wall -pedantic -Iinc
LIBS=-lboost_system -L/usr/lib/ -lboost_thread
SERVER_BIN=server
CLIENT_BIN=client
SERVER_SRC=server.cpp server.hpp server_connect.hpp server_connect.cpp message.cpp message.hpp output.hpp output.cpp
CLIENT_SRC=client.cpp client_connect.hpp client_connect.cpp message.cpp message.hpp output.hpp output.cpp

#maze.hpp maze.cpp
#maze.hpp maze.cpp

all: server client


server: $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) $(LIBS) -o $(SERVER_BIN)


client: $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(LIBS) -o $(CLIENT_BIN)
	
	
clean:
	rm   *.o $(SERVER_BIN) $(CLIENT_BIN)
