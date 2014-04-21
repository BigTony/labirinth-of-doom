// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// output.cpp


#include "output.hpp"

output_handler out;

output_handler::output_handler(){

}

void output_handler::print(std::string message){
	std::cout << message << std::endl;
}

void output_handler::print(int message){
	std::cout << message << std::endl;
}

void output_handler::print(unsigned int message){
	std::cout << message << std::endl;
}