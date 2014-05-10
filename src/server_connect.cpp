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
#include "maze.hpp"



using boost::asio::ip::tcp;

client_connection::client_connection(tcp::socket socket,game_server* gs_ptr): socket_(std::move(socket)){
	game_server_ptr_=gs_ptr;
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
			recived_ = std::atoi(header);
			read_msg();
		}
		else{
			out.print_error(std::string("Unable recive msg. Client NO: ") + std::to_string(client_id_) +std::string(" hang out unexpectly"));
			status_=CONNECTION_LOST;
			socket_.close();
			return;
		} 
	});
}


void client_connection::read_msg(){
	boost::asio::async_read(socket_,boost::asio::buffer(data_, recived_),[this](boost::system::error_code error, std::size_t length){
		if (!error){
			recived_data_=data_;
			out.print_debug("Recived data:\t"+recived_data_);
			
			wait_msg();
		}
		else{
			out.print_error(std::string("Unable to send msg to client NO: ") + std::to_string(client_id_) +std::string(" hang out unexpectly"));
			status_=CONNECTION_LOST;
			socket_.close();
			return;
		}
	});
}


void client_connection::wait_msg_handle(){
	boost::asio::async_read(socket_,boost::asio::buffer(header_, HEADER_LENGTH),[this](boost::system::error_code error, std::size_t length){
		auto self(shared_from_this());
		if (!error){
			char header[HEADER_LENGTH + 1] = "";
			std::strncat(header, header_, HEADER_LENGTH);
			recived_ = std::atoi(header);
			read_msg_handle();
		}
		else{
			out.print_error(std::string("Unable recive msg. Client NO: ") + std::to_string(client_id_) +std::string(" hang out unexpectly"));
			status_=CONNECTION_LOST;
			socket_.close();
			(game_server_ptr_->*next_msg_handler_)(self);
		} 
	});
}


void client_connection::read_msg_handle(){
	boost::asio::async_read(socket_,boost::asio::buffer(data_, recived_),[this](boost::system::error_code error, std::size_t length){
		auto self(shared_from_this());
		if (!error){
			recived_data_=data_;
			out.print_debug("Recived data:\t"+recived_data_);
			(game_server_ptr_->*next_msg_handler_)(self);
		}
		else{
			out.print_error(std::string("Unable to send msg to client NO: ") + std::to_string(client_id_) +std::string(" hang out unexpectly"));
			status_=CONNECTION_LOST;
			socket_.close();
			(game_server_ptr_->*next_msg_handler_)(self);
		}
	});
}

void client_connection::set_status(int status){
	status_=status;
}
int client_connection::get_status(){
	return (status_);
}

std::string client_connection::get_msg(){
	return recived_data_;
}

void client_connection::set_handler(void(game_server::*handler)(std::shared_ptr<client_connection>)){
	next_msg_handler_=handler;
}

void client_connection::set_name(std::string name){
	name_=name;
}
std::string client_connection::get_name(){
	return name_;
}

void client_connection::send_msg(std::string message){
	out.print_debug(std::string("Sending msg to server, socket to server is")+ std::to_string(socket_.is_open()));
	msg_quee_.push_back(message);
	if (msg_quee_.size()==1){
		while (!(msg_quee_.empty())){
			send_quee_msg(msg_quee_.back());
			msg_quee_.pop_back();
		}
	}
}


void client_connection::send_quee_msg(std::string message){
	if (message.length()>MAX_MSG_LENGTH) {
		out.print_warn("Msg is too long for transmit");
		return;
	}
	out.print_debug(std::string("Sending msg to client NO: ") +std::string(" data:\t")+message);	
	char header[HEADER_LENGTH+1]="";
	std::sprintf(header, "%5d", message.length());
	send_data_=header+message;
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

void client_connection::parse_arguments(std::string message){
	if(message.compare(0,8, "send_cmd") == 0){
		if(message.compare(9,13, "open") == 0){
			std::cout << "open" << std::endl;
		}else if(message.compare(9,11, "go") == 0){
			std::cout << "go" << std::endl;
		}else if(message.compare(9,13, "stop") == 0){
			std::cout << "stop" << std::endl;
		}else if(message.compare(9,13, "left") == 0){
			std::cout << "left" << std::endl;
		}else if(message.compare(9,13, "right") == 0){
			std::cout << "right" << std::endl;
		}else if(message.compare(9,13, "take") == 0){
			std::cout << "take" << std::endl;
		}else{
			// spatny prikaz
		}
	}else if(message.compare(0,15, "send_get_lobbys") == 0){
		std::cout << "client zada o lobby" << std::endl;
	}else if(message.compare(0,15, "send_get_mazes") == 0){
		std::cout << "client zada o hry" << std::endl;
	}else if(message.compare(0,4, "join") == 0){
		unsigned int i = 5;
		std::string number;
		while(i < message.length()){
			number += message[i];
			i++;
		}
		int join_number = std::stoi(number);
		std::cout << join_number << std::endl;
	}else if(message.compare(0,10, "disconnect") == 0){
		std::cout << "client provedl disconnect" << std::endl;
	}else if(message.compare(0,4, "exit") == 0){
		std::cout << "client provedl exit" << std::endl;
	}else if(message.compare(0,6, "create") == 0){
		int comma = 0;
		unsigned int i = 7;
		std::string game_name,maze_name,tik_tak;
		while(i < message.length()){
			if(message[i] == '-'){
				comma++;
				i++;
			}
			if(comma == 0){
				game_name += message[i];
			}else if(comma == 1){
				maze_name += message[i];
			}else if(comma == 2){
				tik_tak += message[i];
			}
			i++;
		}
		std::cout << game_name << " " << maze_name << " " << tik_tak << std::endl;
	}else if(message.compare(0,2, "gm") == 0){
		if(message.compare(3,8, "start") == 0){
			std::cout << "gm client: start" << std::endl;
		}else if(message.compare(3,10, "restart") == 0){
			std::cout << "gm client: restart" << std::endl;
		}else if(message.compare(3,7, "stop") == 0){
			std::cout << "gm client: stop" << std::endl;
		}else if(message.compare(3,7, "kick") == 0){
			std::cout << "gm client: kick #asi tu pak bude num zatim neresim" << std::endl;
		}else{
			// spatny gm prikaz
		}
	}else{
		// error
	}
}

connection_binnder::connection_binnder(boost::asio::io_service* io_service, const tcp::endpoint& endpoint)
: acceptor_(*io_service, endpoint), socket_(*io_service),new_client_(0){
	io_=io_service;
	connection_counter_=0;
}

void connection_binnder::wait_connection(game_server* gs_ptr){
	
	acceptor_.async_accept(socket_,[this,gs_ptr](boost::system::error_code error){
		if (!error){
			std::cout << "New client Connecting..." << "actual connection counter: " << connection_counter_ << std::endl;
			client_connection_ptr p_new_connection = std::make_shared<client_connection>(std::move(socket_),gs_ptr);
			connections_.push_back(p_new_connection);
			new_client_ptr_=p_new_connection;
			p_new_connection->set_status(CONNECTED);
			p_new_connection->set_name(std::string("player")+std::to_string(connection_counter_));
			connections_.back()->set_client_id(connection_counter_++);
			new_client_.post();
		} 
		wait_connection(gs_ptr);
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
		if(connections_[i]->get_client_id() == id){ 
			connections_[i]->send_msg(msg);
			break;
		}
	}
	
}
client_connection_ptr connection_binnder::wait_new_client(){
	new_client_.wait();
	return new_client_ptr_;
}









