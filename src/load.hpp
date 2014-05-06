// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// load.hpp

#ifndef LOAD_HPP
#define LOAD_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include "boost/filesystem.hpp" 
#include <boost/regex.hpp>

/**
* Class storing all information files loaded from path.
* Storing all regex matched files.
*/
class loader{
public:
	/**
  	* A constructor.
  	* Constructor of new file loader.
  	*/
	loader();
	/**
  	* A public function.
  	* Load all files from given path.
  	* Save them to files_.
  	* @param path given path to files 
  	*/ 
	void load_all_files(std::string path);
	/**
  	* A public function.
  	* Print out all files_.
  	*/ 
	void print_files();
	/**
  	* A public function.
  	* Find given files in loaded files, files_.
  	* Save them to matches_.
  	* @param path given path to files 
  	*/ 
	void use_specific(std::string regex);
	/**
  	* A public function.
  	* Print out all matched files, matched_.
  	*/ 
	void print_matched();
private:
	/**
  	* A private variable.
  	* Array storing all matched files.
  	*/ 
	std::vector<std::string> matched_;
	/**
  	* A private variable.
  	* Array storing all loaded files.
  	*/ 
	std::vector<std::string> files_;
};

#endif






