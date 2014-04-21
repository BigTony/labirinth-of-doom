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
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>

//game constants
#DEFINE MAX_MAZE_WIDTH 50
#DEFINE MAX_MAZE_LENGTH 50
#DEFINE MIN_CLOCK 500
#DEFINE MAX_CLOCK 5000
#DEFINE MAX_PLAYERS 4

//game status
#DEFINE STOPED 0
#DEFINE PLAYING 1
#DEFINE ENDED 2
#DEFINE ERROR 3

using std;
/**
 * Virtual
 */
class maze_object {
public:
  maze_object()=0;
private:
    
};

class static_object: public maze_object {
  //virtual key,gate,wall,free
};

class dynamic_object public: maze_object {
  //virtual keeper, player
};

class key_object public: static_object{
  
};

class gate_object public: static_object{
  
};

class wall_object public: static_object{
  
};

class path_free public: static_object{
  
};

class player_object public: dynamic_object{
  
};

class keeper_object public: dynamic_object{
  
};


class maze{
public:
  maze();
  void load_maze(string file_name);
  int do_cycle(); // vrati stav hry
  int get_winner(); // vrati id winnera
  void set_command(int player, string command);
  
private:
  t_size width_;
  t_size length_;
  array<maze_object> maze_array_;
};



class game{
public:
  game();
  void set_command(int id, string command);
  void set_timer(int id, string time);
private:
  int owner_id_;
  int game_state_;
  maze maze_;
  array<int,MAX_PLAYERS> players_id_;  
  boost::posix_time::ptime game_start_;
  boost::posix_time::ptime game_end_;
  boost::posix_time::ptime clock_;
  boost::asio::deadline_timer timer_;
  
  
  
  
};




#endif
