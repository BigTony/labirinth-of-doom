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
	void print(std::string message);
	void print(int message);
	void print(unsigned int message);
private:

};


extern output_handler out;

#endif