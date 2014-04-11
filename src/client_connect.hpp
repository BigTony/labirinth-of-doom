// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// client_connect.hpp



#ifndef CLIENT_CONNECT_HPP
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#define CLIENT_CONNECT_HPP

#define PORT 11500

using boost::asio::ip::tcp;


class server_connection {
public:	

	/** A constructor of server_connection.
	* Also create connection to argv[1]
	*/
	server_connection(char *ip[]);
	/** A public function.
	* Send message to server.
	*/
	send_to_server(std::string message);
	/** A public function.
	* Recieve message from server.
	*/
	recieve_from_server();
	/** A public function.
	* Print recieved message from server.
	*/
	print_message(){
		std::cout.write(buf.data(), len);
	}

private:
	/**
	* A private variable.
	* Asio need to have at least one io_service object.
	*/
	boost::asio::io_service io_service;
	/**
	* A private variable.
	* Convert server name.
	*/
	tcp::resolver resolver(io_service);
	/**
	* A private variable.
	* Create list of endpoints.
	*/
	tcp::resolver::query query;
	/**
	* A private variable.
	* 
	*/
	tcp::resolver::iterator endpoint_iterator;
	/**
	* A private variable.
	* Create socket.
	*/
	tcp::socket socket(io_service);
	/**
	* A private variable.
	* Hold recieved data.
	*/
	boost::array<char, 128> buf;
	boost::system::error_code error;
	/**
	* A private variable.
	* The size of the array which hold recieved data.
	* Prevent buffer overflow.
	*/
	size_t len;

};


/**
* 
*/

#endif