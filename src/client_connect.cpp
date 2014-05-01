#include "client_connect.hpp"

using boost::asio::ip::tcp;


server_connection::server_connection(boost::asio::io_service* io,tcp::resolver::iterator endpoint_iterator):socket_(*io){
	io_=io;
	connect(endpoint_iterator);
}

void server_connection::send_prep(const std::string msg){
	io_->post(
        [this, msg]()
        {
            send_msg(msg);
        }
	);
	// *io_->post(send_msg(msg););
}

void server_connection::check_socket(){
	std::cout << "socket klienta prikaz: " << socket_.is_open() << std::endl;
}

void server_connection::send_msg(std::string message){
	std::cout << "socket klienta start: " << socket_.is_open() << std::endl;
	if (message.length()>MAX_MSG_LENGTH) {
		out.print_warn("Msg is too long for transmit");
		return;
	}
	char header[HEADER_LENGTH+1];
	std::sprintf(header, "%5d", message.length());
	send_data_=header+message;
	std::cout << send_data_ << std::endl;
	std::cout << "data: " << send_data_.data() << "delka: " << send_data_.length() << std::endl;
	// send_data_ = message;
	out.print("client_connect:19:posilam zpravu..");
	boost::asio::async_write(socket_, boost::asio::buffer(send_data_.data(),send_data_.length()),[this](boost::system::error_code error, std::size_t){
		out.print("bug1");
		if (!error){
			out.print("bug2");
			std::cout << "Msg transmited to server" << std::endl;

		}
		else{
			out.print("bug3");
			std::cout << "Unable send msg. Server hang out unexpectly" << std::endl;
			status_=CONNECTION_LOST;
			socket_.close();
		}
	});
	std::cout << "socket klienta: " << socket_.is_open() << std::endl;
	std::cout << send_data_ << std::endl;
	//std::cout << error << std::endl;
	out.print("bug");
}

void server_connection::wait_msg(){
	std::cout << "zmrding" << socket_.is_open() << std::endl;
	boost::asio::async_read(socket_,boost::asio::buffer(header_, HEADER_LENGTH),[this](boost::system::error_code error, std::size_t length){
		if (!error){
			char header[HEADER_LENGTH + 1] = "";
			std::strncat(header, header_, HEADER_LENGTH);
			recived_ = std::atoi(header);
			out.print(recived_);

			boost::asio::async_read(socket_,boost::asio::buffer(data_, recived_),[this](boost::system::error_code error, std::size_t length){
				if (!error){
					recived_data_=data_;
					out.print(recived_data_);
					wait_msg();
				}
				else{
					socket_.close();
					std::cout << "Unable recive data. Server hang out unexpectly"<< std::endl;
					return;
				}
			}); 
		}
	else{
		socket_.close();
		std::cout << "Unable recive data(header). Server hang out unexpectly"<< std::endl;
		return;
	}
	});
	
}


void server_connection::connect(tcp::resolver::iterator endpoint_iterator){
	boost::asio::connect(socket_, endpoint_iterator);
	out.print("pripojen klient...");
	wait_msg();
}

void server_connection::stop(){
	socket_.close();
	io_->stop();
}

