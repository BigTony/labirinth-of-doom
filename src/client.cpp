#include "client_connect.hpp"

using boost::asio::ip::tcp;

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
