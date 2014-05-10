// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// client_connect.hpp



#ifndef CLIENT_CONNECT_HPP
#define CLIENT_CONNECT_HPP


#include <iostream>
#include <system_error>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include "output.hpp"
#include "message.hpp"

#define MAX_MSG_LENGTH 4096
#define HEADER_LENGTH 5
#define PORT "11600"
#define NOT_CONNECTED 1
#define CONNECTED 2
#define CONNECTION_LOST 2

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
	/** A public function.
	* Recieve message from server.
	*/
	void wait_msg();
	/** A public function.
	* Print recieved message from server.
	*/
	void sync_wait_msg();
	/** A public function.
	 * Print recieved message from server.
	 */
	std::string get_lobbys();
	std::string get_mazes();
	
	std::string send_create_maze(std::string maze);
	std::string send_get_lobby(std::string lobby);
	void stop();
	void connect(tcp::resolver::iterator endpoint_iterator);
	void check_socket();
	void send_quee_msg(std::string message);
	std::string parse_arguments(std::string message);
	void send_msg(std::string message);
	std::string wait_response();
private:
	

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
	int status_;
	std::string send_data_;
	std::string recived_data_;
	char data_[MAX_MSG_LENGTH+HEADER_LENGTH];
	char header_[HEADER_LENGTH+1];
	int recived_;
	std::vector<std::string> msg_quee_;
	boost::interprocess::interprocess_semaphore mutex_wait_msg_;
	boost::interprocess::interprocess_semaphore mutex_msg_recived_;
};


/**
* 
*/

#endif