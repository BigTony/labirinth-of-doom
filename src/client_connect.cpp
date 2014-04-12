#include "client_connect.hpp"

using boost::asio::ip::tcp;


  server_connection::server_connection(boost::asio::io_service* io,tcp::resolver::iterator endpoint_iterator):socket_(*io){
    io_=io;
    connect(endpoint_iterator);
    // if(connect(endpoint_iterator)){
    //   throw 10;
    // }
  }

  // void server_connection::send_to_server(std::string message){
  //   try{
  //     boost::asio::write(socket_, boost::asio::buffer(message), error);
  //   }
  //   catch(std::exception& e){
  //     std::cerr << e.what() << std::endl;
  //   }
    
  // }

  // void server_connection::recieve_from_server(){
  //   try{
  //     len = socket.read_some(boost::asio::buffer(buf), error);
  //     if (error != boost::asio::error::eof)
  //           throw boost::system::system_error(error); // Some other error.
  //       }
  //       catch(std::exception& e){
  //     std::cerr << e.what() << std::endl;
  //   }
  // }

  // void server_connection::print_message(){
  //   std::cout.write(buf.data(), len);
  // }

  void server_connection::error_biatch(boost::system::error_code error){
    throw 10;
  }

  void server_connection::connect(tcp::resolver::iterator endpoint_iterator){
    // boost::system::error_code *throw_error;
    boost::asio::connect(socket_, endpoint_iterator);
  }

  void server_connection::read_message(){
    std::cout << "OJJJ CONNECT" << std::endl;
  }

  void server_connection::stop(){
    socket_.close();
    io_->stop();
  }

