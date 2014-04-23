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
    game_server server;
    server.run();
    server.terminal_command();
  }
  catch (std::exception& error){
    std::cerr << "Exception: " << error.what() << std::endl;
  }

  return 0;
}


game_server::game_server():io_(),endpoint_(tcp::v4(), SERVER_PORT),binnder_(&io_,endpoint_),t_binnder_([this](){ io_.run(); }){
}



void game_server:: run(){
  binnder_.wait_connection();
}

void game_server::terminal_command(){
    std::getline (std::cin,command_);
    if (command_.compare("exit")==0){
      std::cout << "Stoping game server..." << std::endl;
      binnder_.stop();
      t_binnder_.join();
      return;
    }else if(command_.compare("send")==0){
      binnder_.send_to_client(1,"ROFL");
    }
    terminal_command();


}

