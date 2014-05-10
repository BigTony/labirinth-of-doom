// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// server_connect.hpp



#ifndef SERVER_CONNECT_HPP
#define SERVER_CONNECT_HPP

#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <cstdlib>
#include <boost/asio.hpp>
#include "message.hpp"
#include "output.hpp"
#include "maze.hpp"

#define SERVER_PORT 11600

#define CONNECTED 11
#define IN_MENU 12
#define IN_GAME 13
#define CHOOSING_MAZE 14
#define CHOOSING_GAME 15
#define CONNECTION_LOST -1
#define DISCONNECTED 0

using boost::asio::ip::tcp;
class game_server;
typedef std::shared_ptr<game> game_ptr;
typedef std::vector<game_ptr> games;
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
  client_connection(tcp::socket socket,game_server* gs_ptr);

  /**
  * A public function.
  * Sends message to client connected with this connection.
  * When connection comes handle it and add it to.
  * @param auto 
  */  
  void send_msg(std::string message);
  void wait_handle_msg(std::shared_ptr<client_connection> connection);
  void wait_msg();
  void read_data();
  void set_client_id(int id);
  void read_msg();
  void parse_arguments(std::string message);
  void wait_msg_handle();
  void read_msg_handle();
  void set_status(int status);
  int get_status();
  void set_handler(void(game_server::*handler)(std::shared_ptr<client_connection>));
  std::string get_msg();
  void send_quee_msg(std::string message);
  void set_name(std::string name);
  std::string get_name();
  /**
  * A public variable. 
  * Socket storing information about connection with client.
  */

  
  int get_client_id();
  tcp::socket socket_; 
  
private:
  game_server* game_server_ptr_;
  int client_id_;
  int status_;
  std::string send_data_;
  std::string recived_data_;
  char data_[MAX_MSG_LENGTH+HEADER_LENGTH];
  char header_[HEADER_LENGTH+1];
  int recived_;
  std::vector<std::string> msg_quee_;
  void (game_server::*next_msg_handler_)(std::shared_ptr<client_connection> connection);
  std::string name_;
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
  void wait_connection(game_server* gs_ptr);
  
  /**
  * A public function.
  * Stop waiting for incomming connection from clients.
  */  
  void stop();
  void send_to_client(int id,std::string msg);

  void check_socket();
  client_connection_ptr wait_new_client();
private:  
  
  /**
  * A private variable 
  * Acceptor object needs to be created to listen for new connections
  */  
  tcp::acceptor acceptor_;
  tcp::socket socket_;
  /**
  * A private variable 
  * Array storing client connections
  */   
  std::vector<client_connection_ptr> connections_;

  /**
  * A private variable 
  * Socket storing information about connection with client
  */
  boost::asio::io_service* io_;
  
  int connection_counter_;
  boost::interprocess::interprocess_semaphore new_client_;
  client_connection_ptr new_client_ptr_;
};




/**
* 
*/

#endif
