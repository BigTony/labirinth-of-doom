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
   * Run server.
   */
  void run();
  /**
   * A public function.
   * Handle terminal command.
   */
  void terminal_command();
  /**
   * A public function.
   * Handle clients connection.
   */
  void handle_clients();
  /**
   * A public function.
   * Handle message from client.
   * @param client
   */
  void handle_msg(client_connection_ptr client);
  /**
   * A public function.
   * Generate actual lobbies.
   * Return string
   */
  std::string get_lobbys();
  /**
   * A public function.
   * Generate pointer to game by given name.
   * @param string name of game.
   * Return game_ptr
   */
  game_ptr get_game_by_name(std::string name);
  
  
  
private:
  /**
   * A private variable.
   * Boost io service
   */
  boost::asio::io_service io_;
  /**
   * A private variable.
   * Endpoint.
   */
  tcp::endpoint endpoint_;
  /**
   * A private variable.
   * Binnder for connections.
   */
  connection_binnder binnder_;
  /**
   * A private variable.
   * Binnder thread.
   */
  boost::thread *t_binnder_;
  /**
   * A private variable.
   * Handle client thread.
   */
  boost::thread *t_client_handle_;
  /**
   * A private variable.
   * Command string.
   */
  std::string command_;
  /**
   * A private variable.
   * Class loader.
   */
  loader load_;
  /**
   * A private variable.
   * Class games.
   */
  games games_;
  
};














#endif
