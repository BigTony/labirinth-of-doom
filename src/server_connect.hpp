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
#include "message.hpp"
#include "output.hpp"

#define SERVER_PORT 11600
#define NOT_CONNECTED 1
#define CONNECTED 2
#define CONNECTION_LOST 2

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
  void send_msg(std::string message);
  void wait_msg();
  void read_data();
  void set_client_id(int id);
  void read_msg();

  /**
  * A public variable. 
  * Socket storing information about connection with client.
  */
  tcp::socket socket_;
  
  int get_client_id();
  
  
private:1
  int client_id_;
  int status_;
  std::string send_data_;
  std::string recived_data_;
  char data_[MAX_MSG_LENGTH+HEADER_LENGTH];
  char header_[HEADER_LENGTH+1];
  int recived_;
};


/**
* Handling all incomming cnnections
*/
class connection_binnder {
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
  void send_to_client(int id,std::string msg);
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
  
  int connection_counter_;
  
};




/**
* 
*/

#endif
