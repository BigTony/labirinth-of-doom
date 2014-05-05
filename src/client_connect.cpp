#include "client_connect.hpp"

using boost::asio::ip::tcp;


server_connection::server_connection(boost::asio::io_service* io,tcp::resolver::iterator endpoint_iterator):socket_(*io){
	out.print_debug("Creating server connection");
	io_=io;
	connect(endpoint_iterator);
}

void server_connection::check_socket(){
	out.print_debug("Socket to server is "+ std::to_string(socket_.is_open()));
}

void server_connection::send_msg(std::string message){
	out.print_debug(std::string("Sending msg to server, socket to server is")+ std::to_string(socket_.is_open()));
	if (message.length()>MAX_MSG_LENGTH) {
		out.print_warn("Msg is too long for transmit");
		return;
	}
	char header[HEADER_LENGTH+1];
	std::sprintf(header, "%5d", message.length());
	send_data_=header+message;
	std::cout << send_data_ << std::endl;
	boost::asio::async_write(socket_, boost::asio::buffer(send_data_.data(),send_data_.length()),[this](boost::system::error_code error, std::size_t){
		if (!error){
			out.print_debug("Msg was send");
		}
		else{
			out.print_error("Unable send msg. Server hang out unexpectly");
			status_=CONNECTION_LOST;
			socket_.close();
		}
	});
}

void server_connection::wait_msg(){
	out.print_debug(std::string("Waiting msg from server,socket to server is")+ std::to_string(socket_.is_open()));
	boost::asio::async_read(socket_,boost::asio::buffer(header_, HEADER_LENGTH),[this](boost::system::error_code error, std::size_t length){
		if (!error){
			char header[HEADER_LENGTH + 1] = "";
			std::strncat(header, header_, HEADER_LENGTH);
			recived_ = std::atoi(header);
			boost::asio::async_read(socket_,boost::asio::buffer(data_, recived_),[this](boost::system::error_code error, std::size_t length){
				if (!error){
					recived_data_=data_;
					out.print(recived_data_);
					wait_msg();
				}
				else{
					socket_.close();
					status_=CONNECTION_LOST;
					out.print_error("Unable send msg. Server hang out unexpectly(in msg body)");
					return;
				}
			}); 
		}
	else{
		socket_.close();
		status_=CONNECTION_LOST;
		out.print_error("Unable send msg. Server hang out unexpectly(in msg head)");
		return;
	}
	});
	
}


void server_connection::connect(tcp::resolver::iterator endpoint_iterator){
	boost::asio::connect(socket_, endpoint_iterator);
	out.print_error("Client is connected to server ...");
	wait_msg();
}

void server_connection::stop(){
	socket_.close();
	io_->stop();
}

