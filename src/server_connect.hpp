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
* Class storing all information about connected clients
*/
class client_connection {
public:

  /**
  * A constructor.
  * Constructor of connection_binnder no parrams need.
  * @param boos::asio::io_service needed for I/O opperatoins 
  */
  client_connection(tcp::socket socket);
  ~client_connection();

  /**
  * A public function.
  * Sends message to client connected with this connection
  * When connection comes handle it and add it to
  * @param auto 
  */  
  void send_msg();
    
private:

  /**
  * A private variable 
  * Socket storing information about connection with client
  */
  tcp::socket socket_;  
};


/**
* Handling all incomming cnnections
*/
class connection_binnder {
public:
  
  /**
  * A constructor.
  * Constructor of connection_binnder
  * @param boos::asio::io_service needed for I/O opperatoins 
  */
  connection_binnder(boost::asio::io_service& io);
  ~connection_binnder();
  /**
  * A public function.
  * Waiting for incomming connection from clients.
  * When connection comes handle it and add it to @var connections
  */  
  void wait_connection();
private:
 
  /**
  * A private function.
  * Add new client to known list
  * And add assynchronyose hanndler to IO service
  */  
  void add_connection();  
  
  /**
  * A private variable 
  * Acceptor object needs to be created to listen for new connections
  */  
  tcp::acceptor acceptor_;
  
  /**
  * A private variable 
  * Array storing client connections
  */   
  std::vector<client_connection> connections_;

  /**
  * A private variable 
  * Socket storing information about connection with client
  */
  tcp::socket socket_;
};




/**
* 
*/

#endif
