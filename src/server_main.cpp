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
	  if (argc == 2){
	  std::string arg = argv[1];
	  if (arg.compare("-debug")==0){
		  out.set_debug(true);
	  }}
    game_server server;
    server.run();
    server.terminal_command();
  }
  catch (std::exception& error){
    out.print_error(std::string("Exception: ")+error.what());
  }

  return 0;
}
