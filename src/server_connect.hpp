// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// server_connect.hpp



#ifndef SERVER_CONNECT_HPP
#define SERVER_CONNECT_HPP


#include <cstdlib>
#include <boost/asio.hpp>

#define SERVER_PORT 11500

using boost::asio::ip::tcp;

/**
* Class storing all information about connected clients
*/
class client_connection:public std::enable_shared_from_this<client_connection> {
public:

  /**
  * A constructor.
  * Constructor of new connected client.
  * @param socket used for connection.
  */
  client_connection(boost::asio::io_service* io_service);

  /**
  * A public function.
  * Sends message to client connected with this connection.
  * When connection comes handle it and add it to.
  * @param auto 
  */  
  void send_msg(std::string msg);

  /**
  * A private variable. 
  * Socket storing information about connection with client.
  */
  tcp::socket socket_; 
private:

 
};


/**
* Handling all incomming cnnections
*/
class connection_binnder:public boost::enable_shared_from_this<connection_binnder>{
public:
  
  /**
  * A constructor.
  * Constructor of connection_binnder
  * @param boost::asio::io_service needed for I/O opperatoins.
  * @param const boost::asio::ip::tcp::endpoint point used for I/O opperatoins.
  */
  connection_binnder(boost::asio::io_service* io_service,
		     const tcp::endpoint& endpoint);

  /**
  * A public function.
  * Waiting for incomming connection from clients.
  * When connection comes handle it and add it to @var connections_
  */  
  void wait_connection();
  
  /**
  * A public function.
  * Stop waiting for incomming connection from clients.
  */  
  void stop();
private:  
  
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
  boost::asio::io_service* io_;
};




/**
* 
*/

#endif
