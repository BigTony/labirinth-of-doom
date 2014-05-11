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


std::string parse_tab(std::string msg,int tab_count);

/**
* Class 
* 
*/
class output_handler{
public:
	/**
    * A constructor.
    * Constructor of new output handler.
    */
	output_handler();
	/**
   	 * A public function.
   	 * 
     * @param message
     */ 
	void print_info(std::string message);
	/**
   	 * A public function.
   	 * 
     * @param message
     */ 
	void print(std::string message);
	/**
   	 * A public function.
   	 * 
     * @param message
     */ 
	void print_warn(std::string message);
	/**
   	 * A public function.
   	 * 
     * @param message
     */ 
	void print_error(std::string message);
	/**
   	 * A public function.
   	 * 
     * @param message
     */ 
	void print_debug(std::string message);
	/**
   	 * A virtual public function.
   	 * 
     * @param message
     */ 
	virtual void print_debug_object(std::string message);
	/**
   	 * A public function.
   	 * 
     */ 
	void print_help();
	/**
   	 * A public function.
   	 * 
   	 * @param set
     */
	void set_debug(bool set);
	/**
   	 * A public function.
   	 * 
     */
	bool get_debug();
	/**
   	 * A public function.
   	 * 
     */
	void print_menu();
protected:
	bool debug_=false;
};

/**
* Class 
* 
*/
class input_handler{
public:
	/**
    * A constructor.
    * Constructor of new input handler.
    */
	input_handler();
	/**
   	 * A public function.
   	 * 
   	 * Return string
     */
	std::string wait_cmd();
};

/**
* Class 
* 
*/
class client_input_handler: public input_handler{
public:
	/**
   	 * A public function.
   	 * 
     */
	void print_debug_object(std::string message);
	/**
   	 * A public function.
   	 * 
   	 * Return string
     */
	std::string wait_cmd();
};

/**
* Class 
* 
*/
class client_output_handler: public output_handler{
public:
	/**
   	 * A public function.
   	 * 
     */
	void print_menu();
	/**
   	 * A public function.
   	 * 
   	 * @param menu
     */
	void print_lobbys(std::string menu);
	/**
   	 * A public function.
   	 * 
   	 * @param menu
     */
	void print_mazes(std::string menu);
	/**
   	 * A public function.
   	 * 
   	 * @param response
     */
	void print_response(std::string response);
};

extern client_input_handler clin;
extern client_output_handler clout;
extern input_handler in;
extern output_handler out;

#endif