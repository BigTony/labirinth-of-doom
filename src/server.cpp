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
    while (1){
	command_=in.wait_cmd();
	out.print_menu();
    if (command_.compare("exit")==0){
      out.print_info("Server is shutting down");
      binnder_.stop();
      return;
	}
    else if(command_.compare("load")==0){
	command_=in.wait_cmd();
	load_.load_all_files(command_);
    }
    else if(command_.compare("help")==0){
		out.print_help();
	}
	}
}

void game_server::handle_clients(){
	while(1){
	client_connection_ptr new_client =binnder_.wait_new_client();
	new_client->set_handler(&game_server::handle_msg);
	new_client->wait_msg_handle();
	}
}

void game_server::handle_msg(client_connection_ptr client)
{	
	out.print_debug("Starting handle msg");
	int status=client->get_status();
		out.print_debug(std::string("Message: ")+client->get_msg()+std::string("\n->Is handling..."));
	switch (status){
		case (CONNECTED):
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
// // 			break;
		case (CHOOSING_GAME):{
			out.print_debug(std::string("Client state is CHOOSING_GAME"));
			std::string msg=client->get_msg();
			game_ptr new_game_ptr = get_game_by_name(msg);
			new_game_ptr->add_player(client);
			client->send_msg(new_game_ptr->maze_.msg_send_maze());
			out.print_debug(new_game_ptr->maze_.msg_send_maze());
			client->set_status(IN_GAME);
			break;}
		case (CHOOSING_MAZE):{
			out.print_debug(std::string("Client state is CHOOSING_MAZE"));
			std::string msg=client->get_msg();
			game_ptr new_game_ptr = std::make_shared<game>(client->get_client_id(),load_.get_path()+std::string("/")+parse_tab(msg,0),&io_,parse_tab(msg,1));
			games_.push_back(new_game_ptr);
			client->game_=new_game_ptr;
			new_game_ptr->add_player(client);
			client->send_msg(new_game_ptr->maze_.msg_send_maze());
			out.print_debug(new_game_ptr->maze_.msg_send_maze());
			client->set_status(IN_GAME);
			break;}
		case (IN_GAME):{
			out.print_debug(std::string("Client state is IN_GAME"));
			std::string response =client->game_->terminal_command(client->get_client_id(),client->get_msg());
			client->send_msg(response);
			break;
		}
		default:
			out.print_error(std::string("Unexpected client state")+std::to_string(status));
			return;
	}
	client->wait_msg_handle();
}

std::string game_server::get_lobbys(){
	std::string ret="";
	for (unsigned int i = 0; i < games_.size(); i++)
	{
		ret.append(games_.at(i)->info_to_string());
	}
	return ret;
}

game_ptr game_server::get_game_by_name(std::string name){
	game_ptr game=nullptr;
	for (unsigned int i = 0; i < games_.size(); i++)
	{
		if (games_.at(i)->game_name_.compare(name)==0){
			game = games_.at(i);
		}
	}
	return game;
}