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

client_connection::client_connection(boost::asio::io_service* io_service)
    : socket_(*io_service){
}

void client_connection::set_client_id(int id){
  client_id_=id;
}

int client_connection::get_client_id(){
  return client_id_;
}

void client_connection::wait_msg(){
  
  boost::asio::async_read(socket_,boost::asio::buffer(data, MAX_MSG_LENGTH),
        [this](boost::system::error_code error, std::size_t length)
        {
          if (!error)
          {
            recived_data=data;
          }
          else
          {
            socket_.close();
            std::cout << "Unable recive data. Client hang out unexpectly" << client_id_ << std::endl;
          }
        });
}

void client_connection::send_msg(std::string msg){
      boost::asio::async_write(socket_, boost::asio::buffer(msg.data(),msg.length()),[this](boost::system::error_code error, std::size_t)
        {
          if (!error)
          {
            std::cout << "Msg transmited to client" << client_id_ << std::endl;
          }
          else
          {
            std::cout << "Unable send msg to client. Client ID" << client_id_ << "hang out unexpectly" << std::endl;
            status_=CONNECTION_LOST;
            socket_.close();
          }
        });
  return;
}

connection_binnder::connection_binnder(boost::asio::io_service* io_service, const tcp::endpoint& endpoint)
: acceptor_(*io_service, endpoint){
io_=io_service;
connection_counter_=0;
}
  
void connection_binnder::wait_connection(){
  connections_.emplace_back(io_);
  acceptor_.async_accept(connections_.back().socket_,[this](boost::system::error_code error){
    if (!error){
      std::cout << "New client Connecting..." << "actual connection counter: " << connection_counter_ << std::endl;
      connections_.back().set_client_id(connection_counter_++);
      } 
    wait_connection();
  });   
}

void connection_binnder::stop(){
  acceptor_.cancel();
  io_->stop();
}

void connection_binnder::send_to_client(int id){
  for (unsigned int i = 0; i < connections_.size(); i++)
  {
    std::cout << connections_[i].get_client_id() << std::endl;
    if(connections_[i].get_client_id() == id){ 
      connections_[i].send_msg("YOLO");
      // std::cout << "Zprava odeslana..." << std::endl;
      out.print("zprava odeslana...");
      out.print(10);
      break;
    }
  }

}







    
