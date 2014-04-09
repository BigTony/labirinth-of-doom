#include "client_connection.hpp"

using boost::asio::ip::tcp;

class server_connection {
public: 
  server_connection(char *ip[]){
    query(ip[1], PORT);
    boost::asio::connect(socket, endpoint_iterator);
  }

  send_to_server(std::string message){
    try{
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
    catch(std::exception& e){
      std::cerr << e.what() << std::endl;
    }
    
  }

  recieve_from_server(){
    try{
      len = socket.read_some(boost::asio::buffer(buf), error);
      if (error != boost::asio::error::eof)
            throw boost::system::system_error(error); // Some other error.
        }
        catch(std::exception& e){
      std::cerr << e.what() << std::endl;
    }
  }

  print_message(){
    std::cout.write(buf.data(), len);
  }
};

int main(int argc, char* argv[])
{
  server_connection con(argv);

  while(1){
        std::string message;
        std::cin >> message;
        con.send_to_server(message);
  }

  return 0;
}
