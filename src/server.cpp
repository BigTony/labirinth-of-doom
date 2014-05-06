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
    out.print_error("Exception: "+error.what());
  }

  return 0;
}


game_server::game_server():io_(),endpoint_(tcp::v4(), SERVER_PORT),binnder_(&io_,endpoint_){
  load.load_all_files("./levels");
}



void game_server::run(){
  binnder_.wait_connection();
  t_binnder_ = new boost::thread([this](){ io_.run(); });
}

void game_server::terminal_command(){
    command_=in.wait_cmd();
    if (command_.compare("exit")==0){
      out.print_info("Server is shutting down");
      binnder_.stop();
      t_binnder_->join();
      return;
    }else if(command_.compare("send")==0){
      binnder_.send_to_client(0,"TEST message");
    }else if(command_.compare("socket")==0){
      binnder_.check_socket();
    }
    terminal_command();


}

