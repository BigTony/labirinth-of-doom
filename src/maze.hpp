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

//game constants
#define MAX_MAZE_WIDTH 50
#define MAX_MAZE_LENGTH 50
#define MIN_CLOCK 500
#define MAX_CLOCK 5000
#define MAX_PLAYERS 4

//game status
#define STOPED 0
#define PLAYING 1
#define ENDED 2
#define ERROR 3

class maze_object;
typedef std::shared_ptr<maze_object> maze_object_ptr;

/**
 * Virtual
 */
class maze_object {
public:
  virtual void print_object(){}
  virtual std::string print_to_str();
  virtual int get_steps();
  virtual void set_steps(){}
  virtual std::string get_direction();
  virtual void set_direction(std::string dir);
  virtual int get_state();
  virtual void set_state(int state);
  virtual int get_x();
  virtual int get_y();
  virtual void set_x(int x);
  virtual void set_y(int y);
  virtual int get_before_x();
  virtual int get_before_y();
  virtual void set_before_x(int before);
  virtual void set_before_y(int before);
  virtual void pick_key(unsigned int key_id){};
  virtual int get_id();
  maze_object();
  std::vector<maze_object_ptr> keys_;
private:
	int x_;
  int y_;
  int state_ = 0;
  std::string direction_ = "north";
  int before_x_;
  int before_y_;
  int id;
};

class static_object: virtual public maze_object {
public:
  //virtual key,gate,wall,free
  void print_object() = 0;
  std::string print_to_str() = 0;
  static_object();
};

class dynamic_object: virtual public maze_object {
public:
  //virtual keeper, player
  void print_object() = 0;
  std::string print_to_str() = 0;
  int get_steps() = 0;
  void set_steps() = 0;
  dynamic_object();
  void pick_key(unsigned int key_id);
private:
  int x_;
  int y_;
  int before_;
};

class key_object: public static_object{
public:
  key_object(std::string s_id);
  void print_object();
  std::string print_to_str();
private:
  int id;
};

class gate_object: public static_object{
public:
  gate_object(std::string s_id);
  void print_object();
  std::string print_to_str();
  
private:
  int id;
};

class wall_object: public static_object{
public:
  wall_object();
  void print_object();
  std::string print_to_str();
};

class path_free: public static_object{
public:
  path_free();
  void print_object();
  std::string print_to_str();
};

class player_object: public dynamic_object{
public:
  player_object(std::string s_id);
  void print_object();
  std::string print_to_str();
  int get_steps();
  void set_steps();
private:
  int id;
  int steps_;
};

class keeper_object: public dynamic_object{
public:
  keeper_object(std::string s_id);
  void print_object();
  std::string print_to_str();
  void pick_key(unsigned int key_id){}
  int get_steps();
  void set_steps();
private:
	int id;
  int steps_ = 0;
};

class finish_object: public static_object{
public:
  finish_object();
  void print_object();
  std::string print_to_str();
};

class create_player_object: public static_object{
public:
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


class maze:public std::enable_shared_from_this<maze>{
public:
  maze(std::string maze);
  maze(){};
  void load_maze(std::string file_name);
  int do_cycle(); // vrati stav hry
  int get_winner(); // vrati id winnera
  void set_command(int player, std::string command);
  void add_object(std::string value);
  void print_maze();
  std::string msg_send_maze();

  void set_player_direction(int x,int y,std::string dir);
  void set_direction_keeper(unsigned int keeper_id);
  void set_player_state(int x,int y,int state);
  std::string stop_go();

  void check_collision(unsigned int player_id);
  void check_collision_keeper(unsigned int player_id);
  int get_position(std::string direction);
  std::string check_end();
  std::string move_one(unsigned int player_id);
  std::string move_one_keeper(unsigned int keeper_id);
  void set_maze(std::string level);
  std::string pick_key(int x,int y);
  std::string open_gate(int x,int y);
  void check_key();
  void check_gate();
  void check_steps(int x,int y);
  std::vector<maze_object_ptr> players_;
private:
	int coords_counter_ = 0;
	int width_;
	int length_;
	std::vector<maze_object_ptr> maze_array_;
	std::vector<maze_object_ptr> frees_;
	std::vector<maze_object_ptr> keys_;
	std::vector<maze_object_ptr> gates_;
	std::vector<maze_object_ptr> walls_;
	std::vector<maze_object_ptr> keepers_;
	std::vector<maze_object_ptr> finishes_;
	std::vector<maze_object_ptr> cps_;
};



class game{
public:
	game(int client_id,std::string maze);
	void set_command(int id, std::string command);
	void set_timer(int id, std::string time);
  std::string do_action();
  void set_maze(maze maze);
  void load_maze(std::string maze);
  void terminal_command();
  maze maze_;
private:
	int owner_id_;
	int game_state_;
	std::array<int,MAX_PLAYERS> players_id_;  
	boost::posix_time::ptime game_start_;
	boost::posix_time::ptime game_end_;
	boost::posix_time::ptime clock_;
	// boost::asio::deadline_timer timer_;  
};


class client_maze: public maze,public std::enable_shared_from_this<client_maze>
{
public:
	client_maze(std::string maze);
};



#endif


