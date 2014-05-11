// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// server.hpp

#ifndef server_HPP
#define server_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include "command_handler.hpp"
#include "server_connect.hpp"
#include "load.hpp"

  


/**
* Class 
* 
*/
class game_server{
public:
  /**
   * A constructor.
   * Constructor of new game server.
   */
  game_server();
  /**
   * A destructor.
   * Destructor of game server.
   */
  ~game_server();
  /**
   * A public function.
   * 
   */
  void run();
  /**
   * A public function.
   * 
   */
  void terminal_command();
  /**
   * A public function.
   * 
   */
  void handle_clients();
  /**
   * A public function.
   * 
   * @param client
   */
  void handle_msg(client_connection_ptr client);
  /**
   * A public function.
   * 
   * Return string
   */
  std::string get_lobbys();
  /**
   * A public function.
   * 
   * @param name
   * Return game_ptr
   */
  game_ptr get_game_by_name(std::string name);
  
  
  
private:
  boost::asio::io_service io_;
  tcp::endpoint endpoint_;
  connection_binnder binnder_;
  boost::thread *t_binnder_;
  boost::thread *t_client_handle_;
  std::string command_;
  loader load_;
  games games_;
  
};














#endif
