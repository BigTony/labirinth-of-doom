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

  
/*class command_handler_server_cli: public:command_handler{
public:
  command_handler_server_cli(connection_binnder* binnder);//TODO add running games as param
private:
  connection_binnder* binnder_;
  
};*/

class game_server{
public:
  game_server();
  void run();
  void terminal_command();
  
  
private:
  boost::asio::io_service io_;
  tcp::endpoint endpoint_;
  connection_binnder binnder_;
  boost::thread t_binnder_;
  std::string command_;
};










#endif
