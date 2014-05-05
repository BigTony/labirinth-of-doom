// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// output.hpp

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>
#include <string>


class output_handler{
public:
	output_handler();
	void print_info(std::string message);
	void print(std::string message);
	void print_warn(std::string message);
	void print_error(std::string message);
	void print_debug(std::string message);
	void set_debug(bool set);
	bool get_debug();
private:
	bool debug_=true;
};

class input_handler{
public:
	input_handler();
	std::string wait_cmd();
};

extern input_handler in;
extern output_handler out;

#endif