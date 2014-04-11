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
#include <cstdlib>
#include "server_connect.hpp"


using boost::asio::ip::tcp;

connection_binnder::connection_binnder(boost::asio::io_service* io_service,
					 const tcp::endpoint& endpoint)
: acceptor_(*io_service, endpoint){
io_=io_service;  
}
  
void connection_binnder::wait_connection(){
  connections_.emplace_back(io_);
  acceptor_.async_accept(connections_.back().socket_,[this](boost::system::error_code error){
    if (!error){
      std::cout << "New client Connecting..." << std::endl; 
      }
    wait_connection();
  });   
}

void connection_binnder::stop(){
  acceptor_.cancel();
  io_->post([this](){ connections_.back().socket_.close(); });
  io_->stop();
}




client_connection::client_connection(boost::asio::io_service* io_service)
    : socket_(*io_service){
}


void client_connection::send_msg(){
  return;
}
    
