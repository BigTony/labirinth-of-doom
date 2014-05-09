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
	void print_debug_object(std::string message);
	void set_debug(bool set);
	bool get_debug();
	void print_menu();
private:
	bool debug_=true;
};

class input_handler{
public:
	input_handler();
	std::string wait_cmd();
};


class client_input_handler: public input_handler{
public:
	std::string wait_cmd();
};

class client_output_handler: public output_handler{
public:
	void print_menu();
	void print_lobbys(std::string menu);
	void print_mazes(std::string menu);
};

extern client_input_handler clin;
extern client_output_handler clout;
extern input_handler in;
extern output_handler out;

#endif