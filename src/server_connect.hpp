// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// server_connect.hpp



#ifndef SERVER_CONNECT_HPP
#define SERVER_CONNECT_HPP



#include <boost/asio.hpp>

#define SERVER_PORT "11500"

using boost::asio::ip::tcp;


/**
* Handling all incomming cnnections
*/
class connection_binnder {
public:
  
 /**
  * A constructor.
  * Constructor of connection_binnder no parrams need.
  */
  connection_binnder();
  
 /**
  * A public function.
  * Waiting for incomming connection from clients.
  * When connection comes handle it and add it to @var connections
  */  
  wait_connection();
private:
  
 /**
  * A public function.
  * Waiting for incomming connection from clients.
  * When connection comes handle it and add it to @var connections
  */  
  add_connection();  
  
  
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


/**
* Class storing all information about connected clients
*/
class client_connection {
public:

  client_connection() {
  
}

/**
* 
*/

#endif
