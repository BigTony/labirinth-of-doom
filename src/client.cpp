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

	 client.run();

	 client.terminal_command();
   }
	catch (std::exception& error){
	 std::cerr << "Exception: " << error.what() << std::endl;
   }

	return 0;
  }


game_client::game_client(std::string server_ip):io_(),resolver_(io_),endpoint_(resolver_.resolve({server_ip,PORT})),connection_(&io_,endpoint_){
}

void game_client::run(){
	t_connection_ = new boost::thread([this](){ io_.run(); });
}


void game_client::terminal_command(){
	std::getline (std::cin,command_);
	if (command_.compare("exit")==0){
		std::cout << "Stoping client..." << std::endl;
		connection_.stop();
		t_connection_->join();
		return;
	}else if(command_.compare("send")==0){
		// connection_.send_prep("ROFLAAAA");
		connection_.send_msg("ROFLAAAA");
		// connection_.send_msg("ROFLAAAA");
		std::cout << "=====================" << std::endl;
	}else if(command_.compare("socket")==0){
		connection_.check_socket();
	}
	terminal_command();
  }
