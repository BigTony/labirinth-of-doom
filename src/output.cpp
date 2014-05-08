// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// output.cpp


#include "output.hpp"

output_handler out;
input_handler in;

client_input_handler clin;
client_output_handler clout;

output_handler::output_handler(){

}

void output_handler::print(std::string message){
	std::cout << message << std::endl;
}

void output_handler::print_info(std::string message){
	std::cout << message << std::endl;
}

void output_handler::print_warn(std::string message){
	std::cout << message << std::endl;
}

void output_handler::print_error(std::string message){
	std::cerr << message << std::endl;
}

void  output_handler::print_debug(std::string message){
	if (debug_==true)
		std::cout << message << std::endl;
}

void  output_handler::print_debug_object(std::string message){
	if (debug_==true)
		std::cout << message;
}

void output_handler::set_debug(bool set){
	debug_=set;
}
bool output_handler::get_debug(){
	return debug_;
}

input_handler::input_handler(){
}

std::string input_handler::wait_cmd() {
	std::string command;
	std::getline (std::cin,command);
	std::cout << "----------------------------------" << std::endl;
	return command;
}



std::string client_input_handler::wait_cmd() {
	std::string command;
	std::getline (std::cin,command);
	std::cout << "----------------------------------" << std::endl;
	return command;
}

void client_output_handler::print_menu(){
	std::cout << "----Vytejte ve hre lab of doom-----" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "-----1. Connect--------------------" << std::endl;
	std::cout << "-----2. Create---------------------" << std::endl;
}

void client_output_handler::print_lobbys(std::string menu){
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "-----Choose loby-------------------" << std::endl;
	std::cout << menu << std::endl;
	std::cout << "-----------------------------------" << std::endl;
}

void client_output_handler::print_mazes(std::string menu){
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "-----Choose maze-------------------" << std::endl;
	std::cout << menu << std::endl;
	std::cout << "-----------------------------------" << std::endl;
}
