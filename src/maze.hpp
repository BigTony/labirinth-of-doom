// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// maze.hpp

#ifndef MAZE_HPP
#define MAZE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"


#define MAX_MSG_LENGTH 4096
#define HEADER_LENGTH 5

//game constants
#define MAX_MAZE_WIDTH 50
#define MAX_MAZE_LENGTH 50
#define MIN_CLOCK 500
#define DEFAULT_CLOCK 1500
#define MAX_CLOCK 5000
#define MAX_PLAYERS 4
#define DISCONNECTED 0

//game status
#define STOPED 0
#define PLAYING 1
#define ENDED 2
#define ERROR 3
class game;
class maze_object;
class client_connection;
using boost::asio::ip::tcp;
class game_server;
typedef std::shared_ptr<game> game_ptr;
typedef std::vector<game_ptr> games;
/**
 * Class storing all information about connected clients
 */
class client_connection:public std::enable_shared_from_this<client_connection> {
public:
	
	/**
	 * A constructor.
	 * Constructor of new connected client.
	 * @param socket used for connection.
   * @param gs_ptr pointer to game server
	 */
	client_connection(tcp::socket socket,game_server* gs_ptr);
	
	/**
	 * A public function.
	 * Sends message to client connected with this connection.
	 * When connection comes handle it and add it to.
	 * @param message messsage to send
	 */  
	void send_msg(std::string message);
  /**
   * A public function.
   * Handle message by given connection.
   * @param connection connection to handle.
   */  
	void wait_handle_msg(std::shared_ptr<client_connection> connection);
  /**
   * A public function.
   * Wait to recieve message.
   */ 
	void wait_msg();
  /**
   * A public function.
   * Read data from socket.
   */ 
	void read_data();
  /**
   * A public function.
   * Set client id by id.
   * @param id
   */ 
	void set_client_id(int id);
  /**
   * A public function.
   * Read message from socket.
   */ 
	void read_msg();
  /**
   * A public function.
   * Parse arguments from message.
   * @param message
   */ 
	void parse_arguments(std::string message);
  /**
   * A public function.
   * Handle recieved message.
   */ 
	void wait_msg_handle();
  /**
   * A public function.
   * Read handled message.
   */ 
	void read_msg_handle();
  /**
   * A public function.
   * Set status connection.
   * @param status
   */ 
	void set_status(int status);
  /**
   * A public function.
   * Get status of connection.
   * Return int
   */ 
	int get_status();
  /**
   * A public function.
   * 
   * @param 
   */ 
	void set_handler(void(game_server::*handler)(std::shared_ptr<client_connection>));
  /**
   * A public function.
   * Get message.
   * Return string message variable.
   */ 
	std::string get_msg();
  /**
   * A public function.
   * Add message to que.
   * @param message to que.
   */ 
	void send_quee_msg(std::string message);
  /**
   * A public function.
   * Set name by param.
   * @param name.
   */ 
	void set_name(std::string name);
  /**
   * A public function.
   * Get name.
   * Return string name.
   */ 
	std::string get_name();
	/**
	 * A public variable. 
	 * Socket storing information about connection with client.
	 */
	int get_client_id();
	tcp::socket socket_; 
	game_ptr game_;
	
private:
  /**
   * A private variable.
   * Pointer to game server.
   */ 
	game_server* game_server_ptr_;
	/**
   * A private variable.
   * Hold client id.
   */ 
	int client_id_;
  /**
   * A private variable.
   * Hold game status.
   */ 
	int status_;
  /**
   * A private variable.
   * String data which will be send.
   */ 
	std::string send_data_;
  /**
   * A private variable.
   * String data which will be recieved.
   */ 
	std::string recived_data_;
  /**
   * A private variable.
   * Data buffer.
   */ 
	char data_[MAX_MSG_LENGTH+HEADER_LENGTH];
  /**
   * A private variable.
   * Header buffer.
   */ 
	char header_[HEADER_LENGTH+1];
  /**
   * A private variable.
   * Recieved code.
   */ 
	int recived_;
  /**
   * A private variable.
   * Array of qued messages.
   */ 
	std::vector<std::string> msg_quee_;
  /**
   * A private variable.
   * what.
   */ 
	void (game_server::*next_msg_handler_)(std::shared_ptr<client_connection> connection);
  /**
   * A private variable.
   * Game name.
   */ 
	std::string name_;
};
typedef std::shared_ptr<client_connection> client_connection_ptr;
typedef std::shared_ptr<maze_object> maze_object_ptr;



/**
* Class virtual.
* Used in creating maze objects.
*/
class maze_object {
public:
  /**
   * A virtual public function.
   * Print object to stdout
   */  
  virtual void print_object(){}
  /**
   * A virtual public function.
   * Print object to string.
   * Return string with object name and id.
   */
  virtual std::string print_to_str();
  /**
   * A virtual public function.
   * Get steps of object.
   * Return number of steps by object.
   */
  virtual int get_steps();
  /**
   * A virtual public function.
   * Add to steps variable plus one.
   */
  virtual void set_steps(){}
  /**
   * A virtual public function.
   * Set steps to given param.
   * @param steps steps to set
   */
  virtual void steps_to(int steps){}
  /**
   * A virtual public function.
   * It will return string of object direction.
   * Return string of object direction.
   */
  virtual std::string get_direction();
  /**
   * A virtual public function.
   * Set object direction.
   * @param dir string of direction.
   */
  virtual void set_direction(std::string dir);
  /**
   * A virtual public function.
   * It will return number of object state.
   * Return number of state
   */
  virtual int get_state();
  /**
   * A virtual public function.
   * Set object state.
   */
  virtual void set_state(int state);
  /**
   * A virtual public function.
   * Return number object x cord.
   */
  virtual int get_x();
  /**
   * A virtual public function.
   * Return number object y cord.
   */
  virtual int get_y();
  /**
   * A virtual public function.
   * Set object x coord.
   * @param x number.
   */
  virtual void set_x(int x);
  /**
   * A virtual public function.
   * Set object y coord.
   * @param y number.
   */
  virtual void set_y(int y);
  /**
   * A virtual public function.
   * Return number of x cord before move.
   */
  virtual int get_before_x();
  /**
   * A virtual public function.
   * Return number of y cord before move.
   */
  virtual int get_before_y();
  /**
   * A virtual public function.
   * Set object before move x coord.
   * @param x number.
   */
  virtual void set_before_x(int before);
  /**
   * A virtual public function.
   * Set object before move y coord.
   * @param y number.
   */
  virtual void set_before_y(int before);
  /**
   * A virtual public function.
   * Pick key by given id.
   * @param key_id number.
   */
  virtual void pick_key(unsigned int key_id){};
  virtual int get_id();
  /**
    * A constructor.
    * Constructor of new maze object.
    */
  maze_object();
  /**
    * A public variable.
    * Array storing all keys for player.
    */ 
  std::vector<maze_object_ptr> keys_;
private:
  /**
   * A private variable.
   * Int variable storing x coord of maze objects.
   */ 
	int x_;
  /**
   * A private variable.
   * Int variable storing y coord of maze objects.
   */
  int y_;
  /**
   * A private variable.
   * Int variable storing state of maze objects.
   */
  int state_ = 0;
  /**
   * A private variable.
   * String variable storing direction of maze objects.
   */
  std::string direction_ = "north";
  /**
   * A private variable.
   * Int variable storing before x coord of maze objects.
   */
  int before_x_;
  /**
   * A private variable.
   * Int variable storing before y coord of maze objects.
   */
  int before_y_;
  /**
   * A private variable.
   * Int variable storing id of maze objects.
   */
  int id;
};

/**
* Class virtual.
* Used in creating maze static objects wall,keys etc.. .
*/
class static_object: virtual public maze_object {
public:
  //virtual key,gate,wall,free
  void print_object() = 0;
  std::string print_to_str() = 0;
  /**
   * A constructor.
   * Constructor of new static object.
   */
  static_object();
};

/**
* Class virtual.
* Used in creating maze dynamic objects.
*/
class dynamic_object: virtual public maze_object {
public:
  //virtual keeper, player
  void print_object() = 0;
  std::string print_to_str() = 0;
  int get_steps() = 0;
  void set_steps() = 0;
  void steps_to(int steps) = 0;
  /**
   * A constructor.
   * Constructor of new dynamic object.
   */
  dynamic_object();
  void pick_key(unsigned int key_id);
private:
  int x_;
  int y_;
  /**
   * A private variable.
   * Int variable storing before coord of dynamic maze objects.
   */
  int before_;
};

/**
* Class storing all information about key objects from maze.
*/
class key_object: public static_object{
public:
  /**
   * A constructor.
   * Constructor of new key object.
   */
  key_object(std::string s_id);
  void print_object();
  std::string print_to_str();
private:
  int id;
};

/**
* Class storing all information about gate objects from maze.
*/
class gate_object: public static_object{
public:
  /**
   * A constructor.
   * Constructor of new gate object.
   */
  gate_object(std::string s_id);
  void print_object();
  std::string print_to_str();
private:
  int id;
};

/**
* Class storing all information about wall objects from maze.
*/
class wall_object: public static_object{
public:
  /**
    * A constructor.
    * Constructor of new wall object.
    */
  wall_object();
  void print_object();
  std::string print_to_str();
};

/**
* Class storing all information about free space objects from maze.
*/
class path_free: public static_object{
public:
  /**
    * A constructor.
    * Constructor of new path_free object.
    */
  path_free();
  void print_object();
  std::string print_to_str();
};

/**
* Class storing all information about player objects from maze.
*/
class player_object: public dynamic_object{
public:
  /**
    * A constructor.
    * Constructor of new player object.
    */
  player_object(std::string s_id);
  void print_object();
  std::string print_to_str();
  int get_steps();
  void set_steps();
  void steps_to(int steps);
private:
  int id;
  /**
    * A private variable.
    * Int variable storing number of steps by player.
    */
  int steps_ = 0;
};

/**
* Class storing all information about keeper objects from maze.
*/
class keeper_object: public dynamic_object{
public:
  /**
    * A constructor.
    * Constructor of new keeper object.
    */
  keeper_object(std::string s_id);
  void print_object();
  std::string print_to_str();
  void pick_key(unsigned int key_id){}
  int get_steps();
  void set_steps();
  void steps_to(int steps);
private:
	int id;
  /**
    * A private variable.
    * Int variable storing number of steps by keeper.
    */
  int steps_ = 0;
};

/**
* Class storing all information about finish object from maze.
*/
class finish_object: public static_object{
public:
  /**
    * A constructor.
    * Constructor of new finish object.
    */
  finish_object();
  void print_object();
  std::string print_to_str();
};

/**
* Class storing all information about crate player objects from maze.
* New player will be add to this positions by ids.
*/
class create_player_object: public static_object{
public:
  /**
    * A constructor.
    * Constructor of new create player object.
    */
	create_player_object(std::string s_id);
	void print_object();
  std::string print_to_str();
private:
	int id;
};


typedef std::shared_ptr<path_free> path_free_ptr;
typedef std::shared_ptr<key_object> key_object_ptr;
typedef std::shared_ptr<gate_object> gate_object_ptr;
typedef std::shared_ptr<wall_object> wall_object_ptr;
typedef std::shared_ptr<player_object> player_object_ptr;
typedef std::shared_ptr<keeper_object> keeper_object_ptr;
typedef std::shared_ptr<finish_object> finish_object_ptr;
typedef std::shared_ptr<create_player_object> create_player_object_ptr;


/**
* Class storing all information about maze.
* Maze is basicly most important class for handling game logic.
*/
class maze:public std::enable_shared_from_this<maze>{
public:
  /**
    * A constructor.
    * Constructor of new maze object.
    */
  maze(std::string maze);
  /**
    * A constructor.
    * Constructor of new maze object.
    */
  maze(){};
  /**
   * A public function.
   * Load maze by given name.
   * @param file_name string with maze name.
   */
  void load_maze(std::string file_name);
  /**
   * A public function.
   * Add object to maze object.
   * @param value string object type.
   */
  void add_object(std::string value);
  /**
   * A public function.
   * Print maze.
   */
  void print_maze();
  /**
   * A public function.
   * Return string of whole maze.
   */
  std::string msg_send_maze();
  /**
   * A public function.
   * Set player direction.
   * @param x cord.
   * @param y cord.
   * @param dir direction to set.
   */
  void set_player_direction(int x,int y,std::string dir);
  /**
   * A public function.
   * Set direction to keeper by id.
   * @param keeper_id id of keeper lol.
   */
  void set_direction_keeper(unsigned int keeper_id);
  /**
   * A public function.
   * Set player state.
   * @param x cord.
   * @param y cord.
   * @param state state to set.
   */
  void set_player_state(int x,int y,int state);
  /**
   * A public function.
   * Return update message.
   */
  std::string stop_go();
  /**
   * A public function.
   * Check collison for player.
   * @param player_id id of player.
   */
  void check_collision(unsigned int player_id);
  /**
   * A public function.
   * Check collison for keeper.
   * @param keeper_id id of keeper.
   */
  void check_collision_keeper(unsigned int keeper_id);
  /**
   * A public function.
   * Check if movement of dynamic objects was right.
   * Return update message.
   */
  std::string check_end();
  /**
   * A public function.
   * Accept movement by player.
   * Return update message.
   */
  std::string move_one(unsigned int player_id);
  /**
   * A public function.
   * Accept movement by keeper.
   * Return update message.
   */
  std::string move_one_keeper(unsigned int keeper_id);
  /**
   * A public function.
   * Load maze by level name.
   * @param level name of level.
   */
  void set_maze(std::string level);
  /**
   * A public function.
   * Pick key by player.
   * Return update message.
   */
  std::string pick_key(int x,int y);
  /**
   * A public function.
   * Open gate by player.
   * Return update message.
   */
  std::string open_gate(int x,int y);
  void check_key();
  void check_gate();
  void check_steps(int x,int y);
  /**
   * A public function.
   * Add new player by his id to maze.
   * @param id id of player
   */
  void add_player(int id);
  /**
   * A public function.
   * Check if position is free.
   * Return bool value if space is free.
   */
  bool is_free(int x,int y);
  int set_differ(int differ,int num);
  /**
   * A public function.
   * Update maze by given msg.
   * @param msg update message.
   */
  void maze_update(std::string msg);
  std::vector<maze_object_ptr> players_;
  std::string message_;
  /**
   * A public function.
   * Return keys if player die.
   * Return update message.
   */
  std::string return_keys(unsigned int player_id);
  /**
   * A public function.
   * Disconect player by given id.
   * @param player_id id of player.
   */
  void disconect_player(unsigned int player_id);
protected:
  /**
    * A private variable.
    * Int variable used as coords counter.
    */
	int coords_counter_ = 0;
  /**
    * A private variable.
    * Int variable storing width of maze.
    */
	int width_;
  /**
    * A private variable.
    * Int variable storing length of maze.
    */
	int length_;
  /**
    * A private variable.
    * Array storing all maze objects.
    */
	std::vector<maze_object_ptr> maze_array_;
  /**
    * A private variable.
    * Array storing all path_free objects.
    */
	std::vector<maze_object_ptr> frees_;
  /**
    * A private variable.
    * Array storing all keys objects.
    */
	std::vector<maze_object_ptr> keys_;
  /**
    * A private variable.
    * Array storing all gates objects.
    */
	std::vector<maze_object_ptr> gates_;
  /**
    * A private variable.
    * Array storing all walls objects.
    */
	std::vector<maze_object_ptr> walls_;
  /**
    * A private variable.
    * Array storing all keeper objects.
    */
	std::vector<maze_object_ptr> keepers_;
  /**
    * A private variable.
    * Array storing all finish objects.
    */
	std::vector<maze_object_ptr> finishes_;
  /**
    * A private variable.
    * Array storing all create_player objects.
    */
	std::vector<maze_object_ptr> cps_;
};


/**
* Class storing all information about one game on server.
*/
class game{
public:
  /**
   * A public function.
   * Run game.
   */
	void game_run();
  /**
    * A constructor.
    * Constructor of new game object.
    */
	game(int client_id,std::string maze,boost::asio::io_service *io,std::string name);
	void set_command(int id, std::string command);
	void set_timer(int id, std::string time);
	std::string info_to_string();
  /**
   * A public function.
   * Do one game cycle.
   * Generate update message for client.
   * Return update message.
   */
  std::string do_action();
  void set_maze(maze maze);
  void load_maze(std::string maze);
  /**
   * A public function.
   * Handle player input.
   * Return update message.
   */
  std::string terminal_command(int id, std::string command);
  void add_player(client_connection_ptr ptr);
  void generate_dir(int left_right,int x,int y,int i);
  int players_=0;
  int game_state_=0;
  maze maze_;
  std::string game_name_;
  boost::asio::deadline_timer timer_; 
  boost::posix_time::time_duration clock_;
private:
  boost::posix_time::ptime game_start_;
	int owner_id_;
	std::array<client_connection_ptr,MAX_PLAYERS> players_id_;  
	boost::posix_time::ptime game_end_;
	
	 
	
};

/**
* Virtual class, storing same things like maze on server.
* For drawing etc.. 
*/
class client_maze: public maze,public std::enable_shared_from_this<client_maze>
{
public:
  /**
    * A constructor.
    * Constructor of new client maze object.
    */
	client_maze(std::string maze);

};



#endif


