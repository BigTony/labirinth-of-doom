// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// message.hpp

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#define MAX_MSG_LENGTH 4096

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

class net_msg {
public:
  msg();
  size_t get_length();
  
private:
  string msg_;  
};

class msg_handler{
public:
  msg_handler(array<string> ids, array<string> commands, string separathor);
  void to_net_msg(net_msg* msg,string str);
  void to_string(string* str,net_msg);
  void add_to_net_msg(net_msg* msg,string str);
private:
  
  
};








#endif
