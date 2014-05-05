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

client_connection::client_connection(tcp::socket socket): socket_(std::move(socket)){
}

void client_connection::set_client_id(int id){
	client_id_=id;
}

int client_connection::get_client_id(){
	return client_id_;
}

void client_connection::wait_msg(){
	
	boost::asio::async_read(socket_,boost::asio::buffer(header_, HEADER_LENGTH),[this](boost::system::error_code error, std::size_t length){
		if (!error){
			char header[HEADER_LENGTH + 1] = "";
			std::strncat(header, header_, HEADER_LENGTH);
			std::cout << "prijata data: " << header_ << std::endl;
			recived_ = std::atoi(header);
			// out.print("server_connect:36:delka zpravy:");
			out.print(std::to_string(recived_));
			read_msg();
		}
		else{
			socket_.close();
			std::cout << "Unable recive data(header). Server hang out unexpectly"<< std::endl;
			return;
		} 
	});
}


void client_connection::read_msg(){
	boost::asio::async_read(socket_,boost::asio::buffer(data_, recived_),[this](boost::system::error_code error, std::size_t length){
		if (!error){
			recived_data_=data_;
			out.print(recived_data_);
			// socket_.close();
			wait_msg();
		}
		else{
			std::cout << "fucking error: " << error << " addr: " << socket_.is_open() << std::endl;
			socket_.close();
			std::cout << "Unable recive data. Server hang out unexpectly"<< std::endl;
			return;
		}
	});
	std::cout << "data: " << data_ << std::endl;
}

void client_connection::send_msg(std::string message){
	if (message.length()>MAX_MSG_LENGTH) {
		out.print_warn("Msg is too long for transmit");
		return;
	}
	char header[HEADER_LENGTH+1]="";
	std::sprintf(header, "%5d", message.length());
	send_data_=header+message;
	out.print("TEST");
	boost::asio::async_write(socket_, boost::asio::buffer(send_data_.data(),send_data_.length()),[this](boost::system::error_code error, std::size_t){
		if (!error){
			std::cout << "Msg transmited to client: " << client_id_ << std::endl;
		}
		else{
			std::cout << "Unable send msg to client. Client ID" << client_id_ << "hang out unexpectly" << std::endl;
			status_=CONNECTION_LOST;
			socket_.close();
		}
	});
	return;
}

connection_binnder::connection_binnder(boost::asio::io_service* io_service, const tcp::endpoint& endpoint)
: acceptor_(*io_service, endpoint), socket_(*io_service){
	io_=io_service;
	connection_counter_=0;
}

void connection_binnder::wait_connection(){
	
	acceptor_.async_accept(socket_,[this](boost::system::error_code error){
		if (!error){
			std::cout << "New client Connecting..." << "actual connection counter: " << connection_counter_ << std::endl;
			client_connection_ptr p_new_connection = std::make_shared<client_connection>(std::move(socket_));
			connections_.push_back(p_new_connection);
			connections_.back()->wait_msg();
			connections_.back()->set_client_id(connection_counter_++);
			// connections_.back()->send_msg("cusikfdsafdsa");
		} 
		wait_connection();
	});   
}

void connection_binnder::stop(){
	acceptor_.cancel();
	io_->stop();
}

void connection_binnder::check_socket(){
	std::cout << "socket klienta prikaz: " << connections_[0]->socket_.is_open() << std::endl;
}

void connection_binnder::send_to_client(int id, std::string msg){
	for (unsigned int i = 0; i < connections_.size(); i++)
	{
		std::cout << connections_[i]->get_client_id() << std::endl;
		if(connections_[i]->get_client_id() == id){ 
			connections_[i]->send_msg(msg);
			// std::cout << "Zprava odeslana..." << std::endl;
			out.print("zprava odeslana...");
			break;
		}
	}
	
}








