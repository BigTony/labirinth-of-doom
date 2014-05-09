// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// server.cpp
#include <ctime>
#include <iostream>
#include <string>
#include "server.hpp"
#include "output.hpp"

using boost::asio::ip::tcp;




int main(int argc, char* argv[]){

  try{
	  std::string arg = "argv[1]";
	  if (arg.compare("-debug")){
	  }
    game_server server;
    server.run();
    server.terminal_command();
  }
  catch (std::exception& error){
    out.print_error(std::string("Exception: ")+error.what());
  }

  return 0;
}


game_server::game_server():io_(),endpoint_(tcp::v4(), SERVER_PORT),binnder_(&io_,endpoint_){
  load_.load_all_files("./levels");
}

game_server::~game_server(){
	if (t_binnder_!=nullptr){
		t_binnder_->join();
		delete(t_binnder_);
	}
	if (t_client_handle_!=nullptr){
		t_client_handle_->join();
		delete(t_client_handle_);
	}
}

void game_server::run(){
  binnder_.wait_connection(this);
  t_client_handle_ = new boost::thread([this](){this->handle_clients();  });
  t_binnder_ = new boost::thread([this](){ io_.run(); });

}

void game_server::terminal_command(){
    command_=in.wait_cmd();
    if (command_.compare("exit")==0){
      out.print_info("Server is shutting down");
      binnder_.stop();
      
      return;
    }else if(command_.compare("send")==0){
      binnder_.send_to_client(0,"TEST message");
    }else if(command_.compare("socket")==0){
      binnder_.check_socket();
    }
    terminal_command();
}

void game_server::handle_clients(){
	client_connection_ptr new_client =binnder_.wait_new_client();
	new_client->set_handler(&game_server::handle_msg);
	new_client->wait_msg_handle();
}

void game_server::handle_msg(client_connection_ptr client)
{	
	out.print_debug("Starting handle msg");
	int status=client->get_status();
		out.print_debug(std::string("Message: ")+client->get_msg()+std::string("\n->Is handling..."));
	switch (status){
		case CONNECTED:
			out.print_debug(std::string("Client state is CONNECTED"));
			if (client->get_msg().compare("join")==0){
				client->send_msg(get_lobbys());
				client->set_status(CHOOSING_GAME);
			}
			else if (client->get_msg().compare("create")==0){
				client->send_msg(load_.print_to_string());
				client->set_status(CHOOSING_MAZE);
			}
			else{
				out.print_error(std::string("Unexpected client state")+client->get_msg());
				client->set_status(DISCONNECTED);
			}
			break;
// 		case IN_MENU:
// 			out.print_debug(std::string("Client state is IN_MENU"));
// 			break;
		case CHOOSING_GAME:
			out.print_debug(std::string("Client state is CHOOSING_GAME"));
			game_ptr new_game_ptr = std::make_shared<game>(client->get_client_id(),client->get_msg());
			games_.push_back(new_game_ptr);
			
			break;
		case CHOOSING_MAZE:
			out.print_debug(std::string("Client state is CHOOSING_MAZE"));
			break;
		case IN_GAME:
			out.print_debug(std::string("Client state is IN_GAME"));
			break;
		default:
			out.print_error(std::string("Unexpected client state")+std::to_string(status));
	}
	client->wait_msg_handle();
}

std::string game_server::get_lobbys(){
	std::string ret="";
	for (unsigned int i = 0; i < games_.size(); i++)
	{
		
	}
	return ret;
}