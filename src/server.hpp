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

  



class game_server{
public:
  game_server();
  ~game_server();
  void run();
  void terminal_command();
  void handle_clients();
  void handle_msg(client_connection_ptr client);
  std::string get_lobbys();

  
  
  
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
