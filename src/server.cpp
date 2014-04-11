#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "server_connect.hpp"

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  std::time_t now = std::time(0);
  return std::ctime(&now);
}

int main()
{
  boost::asio::io_service io;
  tcp::endpoint endpoint(tcp::v4(), SERVER_PORT);
  try{
  connection_binnder binnder(&io,endpoint);
  
  //spustit hru;()
  
  io.run();

  }
  catch (std::exception& error){
    std::cerr << "Exception: " << error.what() << std::endl;
  }

  return 0;
}
