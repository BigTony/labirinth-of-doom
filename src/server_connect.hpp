// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// server_connect.hpp



#ifndef SERVER_CONNECT_HPP
#define SERVER_CONNECT_HPP


//connect constants
#define SERVER_PORT 11600
#define CONNECTED 11
#define IN_MENU 12
#define IN_GAME 13
#define CHOOSING_MAZE 14
#define CHOOSING_GAME 15
#define CONNECTION_LOST -1




#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <cstdlib>
#include <boost/asio.hpp>
#include "output.hpp"
#include "maze.hpp"


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
  /**
   * A public function.
   * Send message to client by id.
   * @param id
   * @param msg
   */
  void send_to_client(int id,std::string msg);
  /**
   * A public function.
   * Well check socket.
   */
  void check_socket();
  /**
   * A public function.
   * Return client_connect_ptr.
   */
  client_connection_ptr wait_new_client();
private:  
  
  /**
  * A private variable 
  * Acceptor object needs to be created to listen for new connections
  */  
  tcp::acceptor acceptor_;
  /**
   * A private variable.
   * Socket object needed for communication.
   */
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
  /**
   * A private variable.
   * Count connections.
   */
  int connection_counter_;
  /**
   * A private variable.
   * Semaphore.
   */
  boost::interprocess::interprocess_semaphore new_client_;
  /**
   * A private variable.
   * Pointer to client connection.
   */
  client_connection_ptr new_client_ptr_;
};




/**
* 
*/

#endif
