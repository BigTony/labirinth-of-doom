#include "client_connect.hpp"

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  boost::asio::io_service io;
  tcp::resolver resolver(io);
  auto endpoint_iterator = resolver.resolve({ argv[1],PORT});


  server_connection con(&io,endpoint_iterator);

  io.run();

  return 0;
}
