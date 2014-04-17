#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include "serverhpp"

using boost::asio::ip::tcp;


int main(int argc, char* argv[]){

  try{
    
  
  boost::asio::io_service io;
  tcp::endpoint endpoint(tcp::v4(), SERVER_PORT);
  connection_binnder binnder(&io,endpoint);
  binnder.wait_connection();
  //spustit hru;()
  
  //Start new thread with net services
  std::thread net([&io](){ io.run(); });
  std::string command;
  
  while(1){
    std::getline (std::cin,command);
    if (command.compare("exit")==0){
      std::cout << "Stoping game server..." << std::endl;
      binnder.stop();
      net.join();
      break;
    }
  }
  
  }
  catch (std::exception& error){
    std::cerr << "Exception: " << error.what() << std::endl;
  }

  return 0;
}
