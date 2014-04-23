// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// client.cpp
#include "client_connect.hpp"
#include "client.hpp"


using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
	try{  
	 game_client client(argv[1]);
	 client.terminal_command();
   }
	catch (std::exception& error){
	 std::cerr << "Exception: " << error.what() << std::endl;
   }

	return 0;
  }


game_client::game_client(std::string server_ip):io_(),resolver_(io_),endpoint_(resolver_.resolve({server_ip,PORT})),connection_(&io_,endpoint_){
  }

void game_client::run (){

  }


void game_client::terminal_command(){
	std::getline (std::cin,command_);
	if (command_.compare("exit")==0){
		std::cout << "Stoping game server..." << std::endl;
		connection_.stop();
		t_connection_.join();
		return;
	}else if(command_.compare("send")==0){
	connection_.send_msg("ROFLAAAA");
	}
	terminal_command();
  }
