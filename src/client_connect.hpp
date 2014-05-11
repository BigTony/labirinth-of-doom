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
#include "maze.hpp"

#define MAX_MSG_LENGTH 4096
#define HEADER_LENGTH 5
#define PORT "11600"
#define NOT_CONNECTED 1
#define CONNECTED 2
#define CONNECTION_LOST 2

using boost::asio::ip::tcp;

/**
* Class 
* 
*/
class server_connection {
public:
	/** 
	 * A constructor of server_connection.
	 * Also create connection to argv[1]
	 */
	server_connection(boost::asio::io_service *io,tcp::resolver::iterator endpoint_iterator);
	/** 
	 * A public function.
	 * Recieve message from server.
	 */
	void wait_msg();
	/** 
	 * A public function.
	 * Print recieved message from server.
	 */
	void sync_wait_msg();
	/**
   	 * A public function.
     * Wait for update.
     * @param maze_ptr
     */ 
	void wait_maze_update(client_maze** maze_ptr);
	/** 
	 * A public function.
	 * Print recieved message from server.
	 * Return string lobbies.
	 */
	std::string get_lobbys();
	/**
   	 * A public function.
     * Print recieved messsage from server.
     * Return string mazes.
     */ 
	std::string get_mazes();
	/**
   	 * A public function.
     * Send message to server to create new maze.
     * @param maze maze name.
     * Return string.
     */ 
	std::string send_create_maze(std::string maze);
	/**
   	 * A public function.
   	 * Send to get lobbies.
     * @param lobby.
     * Return string.
     */ 
	std::string send_get_lobby(std::string lobby);
	/**
   	 * A public function.
     * Stop it.
     */ 
	void stop();
	/**
   	 * A public function.
   	 * Connect to server.
     * @param endpoint_iterator
     */ 
	void connect(tcp::resolver::iterator endpoint_iterator);
	/**
   	 * A public function.
     * Check socket if alive or not.
     */ 
	void check_socket();
	/**
   	 * A public function.
   	 * Send msg to que for send.
     * @param message
     */ 
	void send_quee_msg(std::string message);
	/**
   	 * A public function.
   	 * Parse arguments.
     * @param message.
     */ 
	std::string parse_arguments(std::string message);
	/**
   	 * A public function.
   	 * Send message to server.
     * @param message
     */ 
	void send_msg(std::string message);
	/**
   	 * A public function.
     * Synchronize messages.
     * Return string
     */ 
	std::string sync_msg();
	tcp::socket socket_;
private:
	/**
	* A private variable.
	* Asio need to have at least one io_service object.
	*/
	boost::asio::io_service *io_;

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
	/**
   	 * A private variable.
     * Status.
     */
	int status_;
	/**
   	 * A private variable.
     * Data which will be send to server.
     */
	std::string send_data_;
	/**
   	 * A private variable.
     * Recieved data from message.
     */
	std::string recived_data_;
	/**
   	 * A private variable.
     * Buffer for data.
     */
	char data_[MAX_MSG_LENGTH+HEADER_LENGTH];
	/**
   	 * A private variable.
     * Buffer for header.
     */
	char header_[HEADER_LENGTH+1];
	/**
   	 * A private variable.
     * Recieved signal.
     */
	int recived_;
	/**
   	 * A private variable.
     * Array of messages.
     */
	std::vector<std::string> msg_quee_;
	/**
   	 * A private variable.
     * Semaphore.
     */
	boost::interprocess::interprocess_semaphore mutex_wait_msg_;
	/**
   	 * A private variable.
     * Semaphore.
     */
	boost::interprocess::interprocess_semaphore mutex_msg_recived_;
};


/**
* 
*/

#endif