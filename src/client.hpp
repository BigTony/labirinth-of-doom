// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// client.hpp

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "client_connect.hpp"
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include "maze.hpp"

using boost::asio::ip::tcp;

/**
 * Class 
 * 
 */
class game_client{
  public:
  /**
   * A constructor.
   * Constructor of new game client.
   */
  game_client(std::string server_ip);
  /**
   * A destructor.
   * Destructor of game client.
   */
  ~game_client();
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
  void choose_lobby();
  /**
   * A public function.
   * 
   */ 
  void choose_maze();
  /**
   * A public function.
   * 
   * @param maze
   */ 
  void create_game(std::string maze);
  /**
   * A public function.
   * 
   * @param lobby
   */ 
  void join_game(std::string lobby);
  /**
   * A public function.
   * 
   */ 
  void play_game();
  
private:
  /**
   * A private variable.
   * Boost Io_service.
   */
  boost::asio::io_service io_;
  /**
   * A private variable.
   * Tcp resolver.
   */
  tcp::resolver resolver_;
  /**
   * A private variable.
   * Endpoint iterator.
   */
  tcp::resolver::iterator endpoint_;
  /**
   * A private variable.
   * connection to server.
   */
  server_connection connection_;
  /**
   * A private variable.
   * String command.
   */
  std::string command_;
  /**
   * A private variable.
   * Thread.
   */
  boost::thread *t_connection_;
  /**
   * A private variable.
   * Client maze for showing maze.
   */
  client_maze *maze_ptr_;
};

#endif
