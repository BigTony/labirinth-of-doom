// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// client_connect.hpp



#ifndef CLIENT_CONNECT_HPP
#include <iostream>
#include <system_error>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#define CLIENT_CONNECT_HPP

#define PORT "11500"

using boost::asio::ip::tcp;


class server_connection {
public:	

	/** A constructor of server_connection.
	* Also create connection to argv[1]
	*/
	server_connection(boost::asio::io_service *io,tcp::resolver::iterator endpoint_iterator);
	/** A public function.
	* Send message to server.
	*/
	void send_to_server(std::string message);
	/** A public function.
	* Recieve message from server.
	*/
	void recieve_from_server();
	/** A public function.
	* Print recieved message from server.
	*/
	void print_message(){
		std::cout.write(buf_.data(), len_);
	}
	void stop();
	void connect(tcp::resolver::iterator endpoint_iterator);

	void error_biatch(boost::system::error_code error);
private:
	
	void read_message();

	/**
	* A private variable.
	* Asio need to have at least one io_service object.
	*/
	boost::asio::io_service *io_;
	/**
	* A private variable.
	* Create socket.
	*/
	tcp::socket socket_;
	/**
	* A private variable.
	* Hold recieved data.
	*/
	boost::array<char, 128> buf_;
	/**
	* A private variable.
	* The size of the array which hold recieved data.
	* Prevent buffer overflow.
	*/
	size_t len_;
};


/**
* 
*/

#endif