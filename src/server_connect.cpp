// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// server_connect.cpp
#include <ctime>
#include <iostream>
#include <string>
#include "server_connect.hpp"


using boost::asio::ip::tcp;


class connection_binnder {
public:
  
 /**
  * A constructor.
  * Constructor of connection_binnder no parrams need.
  */
  connection_binnder(){   
  acceptor(io_service, tcp::endpoint(tcp::v4(), SERVER_PORT));    
  }
  
 /**
  * A public function.
  * Waiting for incomming connection from clients.
  * When connection comes handle it and add it to @var connections
  */  
  wait_connection();
private:
  /**
  * A private variable 
  * Any program that uses asio need to have at least one io_service object
  */  
  boost::asio::io_service io_service;
  
  
  /**
  * A private variable 
  * Acceptor object needs to be created to listen for new connections
  */  
  tcp::acceptor;
  
  /**
  * A private variable 
  * Array storing client connections
  */   
  client_connection * connections;
  
  
}