#include "client_connect.hpp"
#include <thread>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
  try{

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

catch (std::exception& error){
    std::cerr << "Exception: " << error.what() << std::endl;
  }
// catch(int &kunda){a
//   std::cout << " chytl sem intpokemona"<< kunda << std::endl;
// }
// catch (std::string &s){
//   std::cout << " chytl sem stringokemona"<< s << std::endl;
//   // std::cout << s << std::endl;
// }



  return 0;
}
