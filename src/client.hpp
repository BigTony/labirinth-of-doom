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

class game_client{
  public:
  game_client(std::string server_ip);
  void run();
  void terminal_command();
  void choose_lobby();
  void choose_maze();
  void create_game(std::string maze);
  void join_game(std::string lobby);
  void play_game();
  
private:
  boost::asio::io_service io_;
  tcp::resolver resolver_;
  tcp::resolver::iterator endpoint_;
  server_connection connection_;
  std::string command_;
  boost::thread *t_connection_;
  client_maze maze_;
};

#endif
