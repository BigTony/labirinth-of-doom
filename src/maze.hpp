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
  maze_object();
private:
    
};

class static_object: public maze_object {
public:
  //virtual key,gate,wall,free
  static_object();
};

class dynamic_object: public maze_object {
public:
  //virtual keeper, player
  dynamic_object();
};

class key_object: public static_object{
public:
  key_object(std::string s_id);
private:
  int id;
};

class gate_object: public static_object{
public:
  gate_object(std::string s_id);
private:
  int id;
};

class wall_object: public static_object{
public:
  wall_object();
};

class path_free: public static_object{
public:
  path_free();
};

class player_object: public dynamic_object{
public:
  player_object();
private:
  int id;
};

class keeper_object: public dynamic_object{
public:
  keeper_object(std::string s_id);
private:
  int id;
};

class finish_object: public static_object{
public:
  finish_object();
};

class create_player_object: public static_object{
public:
  create_player_object(std::string s_id);
private:
  int id;
};


class maze{
public:
  maze();
  void load_maze(std::string file_name);
  int do_cycle(); // vrati stav hry
  int get_winner(); // vrati id winnera
  void set_command(int player, std::string command);
  void add_object(std::string value);
  
private:
  int width_;
  int length_;
  std::vector<maze_object> maze_array_;
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
