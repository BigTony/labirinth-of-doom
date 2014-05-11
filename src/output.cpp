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




std::string parse_tab(std::string msg,int tab_count){
	std::string name = "";
	int i = 0;
	int len = msg.size();
	int tab_count_stop = 0;
	while(tab_count_stop < tab_count){
		if(msg[i] == '\t'){
			tab_count_stop++;
		}
		i++;
	}
	while(msg[i] != '\t'){
		if(i==len){
			break;
		}
		name += msg[i];
		i++;
	}
	return name;
}


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

void output_handler::print_menu(){
	std::cout << "----Server Lab of doom-------------" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "-----1. load-----------------------" << std::endl;
	std::cout << "-----2. exit-----------------------" << std::endl;
}

void output_handler::print_help(){
	std::cout << "Server for game Lab of doom --posible commands:" << std::endl;
	std::cout << "load to load path with maps(default is /examples)" << std::endl;
	std::cout << "Map format: w\\nl\\n following csv with ',' as divider." << std::endl;
	std::cout << "Where:" << std::endl;	
	std::cout << "exit" << std::endl;
}

std::string client_input_handler::wait_cmd() {
	std::string command;
	std::getline (std::cin,command);
	std::cout << "----------------------------------" << std::endl;
	return command;
}

void client_output_handler::print_menu(){
	std::cout << "----Client Lab of doom-------------" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "-----1. join-----------------------" << std::endl;
	std::cout << "-----2. create---------------------" << std::endl;
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


void client_output_handler::print_response(std::string response){
	std::cout << "---------Response is:--------------" << std::endl;
	std::cout << response << std::endl;
}
