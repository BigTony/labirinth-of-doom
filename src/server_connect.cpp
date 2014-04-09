// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// server_connect.cpp
#include <ctime>
#include <iostream>
#include <string>
#include "server_connect.hpp"


using boost::asio::ip::tcp;


class connection_binnder {
public:
  
  connection_binnder(boost::asio::io_service& io):acceptor(io_service, tcp::endpoint(tcp::v4(), SERVER_PORT)),socket(io_service){
  wait_connection();  
  }
 
  wait_connection(){
    acceptor_.async_accept(socket_,&add_connection();    
  }
  
  add_connection();
  
  
}