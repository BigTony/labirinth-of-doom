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
		std::string arg = argv[1];
		if (arg.compare("-debug")==0)
		{
			out.set_debug(true);
			clout.set_debug(true);
			game_client client(argv[2]);
			client.run();
			client.terminal_command();
		}
		else{
			game_client client(argv[1]);
			client.run();
			client.terminal_command();
		}

   }
	catch (std::exception& error){
	 std::cerr << "Exception: " << error.what() << std::endl;
   }

	return 0;
  }


game_client::game_client(std::string server_ip):io_(),resolver_(io_),endpoint_(resolver_.resolve({server_ip,PORT})),connection_(&io_,endpoint_){
	maze_ptr_=nullptr;
}
game_client::~game_client(){
	if (maze_ptr_!=nullptr){
		delete(maze_ptr_);
	}
}

void game_client::run(){
	connection_.wait_maze_update(&maze_ptr_);
	t_connection_ = new boost::thread([this](){ io_.run(); });
}


void game_client::terminal_command(){
	clout.print_menu();
	command_=clin.wait_cmd();
	if (command_.compare("exit")==0){
		clout.print("Stoping game client");
		connection_.stop();
		t_connection_->join();
		return;
	}else if(command_.compare("create")==0){
		choose_maze();
	}else if(command_.compare("join")==0){
		choose_lobby();
	}else if(command_.compare("send")==0){
		connection_.send_msg("Test msg");
	}else if(command_.compare("socket")==0){
		connection_.check_socket();
	}
	terminal_command();
  }
  
  
  void game_client::choose_lobby(){
	 clout.print_lobbys(connection_.get_lobbys());
	command_=clin.wait_cmd();
	if(command_.compare("back")==0){
		return;
	}
	else{
		join_game(command_);
	}
}
  
  
  void game_client::choose_maze(){
	clout.print_mazes(connection_.get_mazes());
	command_=clin.wait_cmd();
	if(command_.compare("back")==0){
		connection_.send_msg(command_);
		return;
	}
	else if(command_.compare("refresh")==0){
		choose_maze();
	}
	else{
		create_game(command_);
	}
  }
void game_client::create_game(std::string maze){
	clout.print_debug(std::string("Creating new maze: ")+maze);
	std::string lobby= connection_.send_create_maze(maze);
	if (maze_ptr_!=nullptr){
		delete(maze_ptr_);
	}
	maze_ptr_=new client_maze(lobby);
	play_game();
}

void game_client::join_game(std::string lobby){
	clout.print_debug(std::string("Joinnig lobby: ")+lobby);
	if (maze_ptr_!=nullptr){
		delete(maze_ptr_);
	}
	std::string maze= connection_.send_get_lobby(lobby);
	maze_ptr_=new client_maze(maze);
	play_game();
}

void game_client::play_game(){
	clout.print_debug("Starting playing game...");
// 	io_.post([this]{connection_.socket_.cancel();});
// 	connection_.wait_maze_update(maze_ptr_);
	maze_ptr_->print_maze();
	std::string response;
	while (1){
		command_=clin.wait_cmd();
		connection_.send_msg(command_);
		response=connection_.sync_msg();
		clout.print_debug("Response was returned");
		clout.print_response(response);
		if (response.compare("exit")==0){
			break;
		}
	}
}

