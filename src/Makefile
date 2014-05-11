CC=g++-4.8
CFLAGS=-g -std=c++11 -pthread -Wall -pedantic -Iinc
LIBS=-lboost_system -L/usr/lib/ -Llib/ -lboost_thread -lboost_filesystem
SERVER_BIN=bludiste2014-server
CLIENT_CLI_BIN=bludiste2014-cli
SERVER_SRC=server_main.cpp server.cpp server.hpp server_connect.hpp server_connect.cpp output.hpp output.cpp load.cpp load.hpp maze.hpp maze.cpp
CLIENT_CLI_SRC=client.cpp client.hpp client_connect.hpp client_connect.cpp output.hpp output.cpp maze.hpp maze.cpp server_connect.hpp server_connect.cpp load.cpp load.hpp server.cpp server.hpp


all: server cli

server: $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) $(LIBS) -o $(SERVER_BIN)

cli: $(CLIENT_CLI_SRC)
	$(CC) $(CFLAGS) $(CLIENT_CLI_SRC) $(LIBS) -o $(CLIENT_CLI_BIN)
	
clean:
	rm   *.o $(SERVER_BIN) $(CLIENT_CLI_BIN)
