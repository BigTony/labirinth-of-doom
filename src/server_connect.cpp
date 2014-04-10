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

  connection_binnder::connection_binnder(boost::asio::io_service& io_service):acceptor_(io_service, tcp::endpoint(tcp::v4(), SERVER_PORT)),socket_(io_service){  
  }
  
  void connection_binnder::wait_connection(){
    acceptor_.async_accept(socket_,&add_connection);    
  }
  
  void connection_binnder::add_connection(const boost::system::error_code& error){
    if (!error)
    {
    std::cout << "New client Connecting..." << std::endl;
    connections_.push_back(client_connection(chat_session(std::move(socket_))));c

    }
  } 

  client_connection::client_connection(tcp::socket socket):socket_(std::move(socket)){
  }

  
  void send_msg(){
    return;
  }
    
