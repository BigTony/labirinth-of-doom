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
   * Run client.
   */ 
  void run();
  /**
   * A public function.
   * Handle commands from player.
   */ 
  void terminal_command();
  /**
   * A public function.
   * Choose lobby..
   */ 
  void choose_lobby();
  /**
   * A public function.
   * Choose maze.
   */ 
  void choose_maze();
  /**
   * A public function.
   * Create game.
   * @param maze level name.
   */ 
  void create_game(std::string maze);
  /**
   * A public function.
   * Join game.
   * @param lobby name of lobby with players.
   */ 
  void join_game(std::string lobby);
  /**
   * A public function.
   * Game loop.
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
