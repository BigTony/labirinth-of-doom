// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// client.cpp
#include "client_connect.hpp"
#include <thread>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
  try{  
  game_client client;
  client.terminal_command();
  }
  catch (std::exception& error){
    std::cerr << "Exception: " << error.what() << std::endl;
  }

  return 0;
  
  
  
  boost::asio::io_service io;
  tcp::resolver resolver(io);
  auto endpoint_iterator = resolver.resolve({ argv[1],PORT});


  server_connection con(&io,endpoint_iterator);
  std::thread net([&io](){ io.run(); });
  std::string command;
  while(1){
    std::getline (std::cin,command);
    if (command.compare("exit")==0){
      std::cout << "Leaving game..." << std::endl;
      con.stop();
      net.join();
      break;
    }
  }

}


game_client::game_client():io_(),resolver_(io_){
  endpoint_
}

void game_client::run (){
  
}


void game_client::terminal_command(){
    std::getline (std::cin,command_);
    if (command_.compare("exit")==0){
      std::cout << "Stoping game server..." << std::endl;
      connection_.stop();
      t_connection_.join();
      break;
    }
    else {
      tcp::resolver resolver(io_);
      endpoint_= resolver.resolve({ string,PORT});
      connection_(&io_,endpoint_);
    }
}
