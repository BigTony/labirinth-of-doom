// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// parser.hpp

#include <iostream>
#include <string> 

class parser_server {
public:
	void parse_arguments(std::string message);
private:

};

class parser_client {
public:
	void parse_arguments(std::string message);
	int getx();
	int gety();
	std::string getmaze();
private:
	int x;
	int y;
	std::string maze;
	// provizorni ulozeni objektu

};