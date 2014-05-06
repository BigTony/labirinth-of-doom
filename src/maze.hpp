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



/**
 * Virtual
 */
class maze_object {
public:
  virtual void print_object(){}
  virtual std::string print_to_str(){}
  maze_object();
private:
  int x;
  int y;
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
  dynamic_object();
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
  player_object();
  void print_object();
  std::string print_to_str();
private:
  int id;
  int x_;
  int y_;
  std::string direction_ = "north";
};

class keeper_object: public dynamic_object{
public:
  keeper_object(std::string s_id);
  void print_object();
  std::string print_to_str();
private:
  int id;
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

typedef std::shared_ptr<maze_object> maze_object_ptr;
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
  maze(std::string level);
  void load_maze(std::string file_name);
  int do_cycle(); // vrati stav hry
  int get_winner(); // vrati id winnera
  void set_command(int player, std::string command);
  void add_object(std::string value);
  void print_maze();
  std::string msg_send_maze();

  void set_player_direction(int x,int y,std::string dir);
private:
  int coords_counter;
  int width_;
  int length_;
  std::vector<maze_object_ptr> maze_array_;
  std::vector<path_free_ptr> frees_;
  std::vector<key_object_ptr> keys_;
  std::vector<gate_object_ptr> gates_;
  std::vector<wall_object_ptr> walls_;
  std::vector<player_object_ptr> players_;
  std::vector<keeper_object_ptr> keepers_;
  std::vector<finish_object_ptr> finishes_;
  std::vector<create_player_object_ptr> cps_;
};



class game{
public:
  game();
  void set_command(int id, std::string command);
  void set_timer(int id, std::string time);
private:
  int owner_id_;
  int game_state_;
  maze maze_;
  std::array<int,MAX_PLAYERS> players_id_;  
  boost::posix_time::ptime game_start_;
  boost::posix_time::ptime game_end_;
  boost::posix_time::ptime clock_;
  boost::asio::deadline_timer timer_;  
};




#endif
