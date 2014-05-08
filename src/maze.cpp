// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// maze.cpp

#include "maze.hpp"
#include "output.hpp"

void maze::print_maze(){	
	for (unsigned int i = 0; i < maze_array_.size(); i++){
		if((i % (width_)) == 0){
			out.print("");
		}
		maze_array_.at(i)->print_object();
	}
	out.print("\n");
}

std::string maze::msg_send_maze(){
	std::string send_maze = std::to_string(width_) + "\n" + std::to_string(length_) + "\n";
	for (unsigned int i = 0; i < maze_array_.size(); i++){
		send_maze.append(maze_array_.at(i)->print_to_str());
		send_maze.append(",");
		if((i % (width_)) == 0){
			send_maze.append("\n");
		}
	}
	return send_maze;
}

void maze::add_object(std::string value){
	maze_object_ptr obj_ptr;
	// std::cout << value << std::endl;
	if(value == ""){
		obj_ptr = std::make_shared<path_free>(path_free());
		frees_.push_back(obj_ptr);
	}else if(value == "w"){
		obj_ptr = std::make_shared<wall_object>(wall_object());
		walls_.push_back(obj_ptr);
	}else if(value == "f"){
		obj_ptr = std::make_shared<finish_object>(finish_object());
		finishes_.push_back(obj_ptr);
	}else if(value.compare(0,2, "G_") == 0){
		obj_ptr = std::make_shared<gate_object>(gate_object(value.substr(2)));
		gates_.push_back(obj_ptr);
	}else if(value.compare(0,2, "S_") == 0){
		obj_ptr = std::make_shared<keeper_object>(keeper_object(value.substr(2)));
		int y = coords_counter_ / width_;
		int x = coords_counter_ - (y * width_);
		obj_ptr->set_x(x);
		obj_ptr->set_y(y);
		keepers_.push_back(obj_ptr);
	}else if(value.compare(0,2, "K_") == 0){
		obj_ptr = std::make_shared<key_object>(key_object(value.substr(2)));
		keys_.push_back(obj_ptr);
	}else if(value.compare(0,2, "P_") == 0){
		obj_ptr = std::make_shared<player_object>(player_object(value.substr(2)));
		int y = coords_counter_ / width_;
		int x = coords_counter_ - (y * width_);
		obj_ptr->set_x(x);
		obj_ptr->set_y(y);
		players_.push_back(obj_ptr);
	}else if(value.compare(0,3, "Cp_") == 0){
		obj_ptr = std::make_shared<create_player_object>(create_player_object(value.substr(3)));
		cps_.push_back(obj_ptr);
	}else{
		return;
	}
	maze_array_.push_back(obj_ptr);

}

maze::maze(){

}

void maze::set_maze(std::string level){
	std::ifstream file ( level );
	std::string value = "";

	if(file.good()){
		getline(file,value);
		width_ = std::stoi(value);
	}
	value = "";
	if(file.good()){
		getline(file,value);
		length_ = std::stoi(value);
	}
	value = "";

	while ( file.good() ){
    	char c = file.get();
    	
		if (file.good()){
			if((c == ',') || (c == '\n')){
				add_object(value);
				coords_counter_++;
				value = "";
			}else{
				value +=c;
			}
		} 

   	}
   	file.close();
}

void maze::stop_go(){
	for (unsigned int i = 0; i < players_.size(); i++){
		if(players_.at(i)->get_state() == 1){
			check_collision(i);
		}
	}

}

void maze::check_collision(unsigned int player_id){
	std::string dir = players_.at(player_id)->get_direction();
	int x = players_.at(player_id)->get_x();
	int y = players_.at(player_id)->get_y();
	if(dir == "north"){
		if(y != 0){
			if((maze_array_.at(x+(y*width_))->print_to_str()) != "w"){
				y--;

				players_.at(player_id)->set_y(y);
				std::cout << "n" << std::endl;
			}		
		}		
	}else if(dir == "west"){
		if(x != 0){
			if((maze_array_.at(x+(y*width_))->print_to_str()) != "w"){
				x--;
				players_.at(player_id)->set_y(y);
				std::cout << "w" << std::endl;
			}		
		}
	}else if(dir == "south"){
		if(y != length_){
			if((maze_array_.at(x+(y*width_))->print_to_str()) != "w"){
				y++;
				players_.at(player_id)->set_y(y);
				std::cout << "s" << std::endl;
			}		
		}
	}else if(dir == "east"){
		if(y != width_){
			if((maze_array_.at(x+(y*width_))->print_to_str()) != "w"){
				x++;
				players_.at(player_id)->set_y(y);
				std::cout << "e" << std::endl;
			}		
		}
	}
}

game::game(){

}

void game::do_action(){	
	maze_.stop_go();
}

void game::set_maze(maze maze){
	maze_ = maze;
}



maze_object::maze_object(){

}

int maze_object::get_x(){
	return x_;
}

int maze_object::get_y(){
	return y_;
}

void maze_object::set_x(int x){
	x_ = x;
}

void maze_object::set_y(int y){
	y_ = y;
}

static_object::static_object(){

}

dynamic_object::dynamic_object(){

}


void dynamic_object::set_direction(std::string dir){
	direction_ = dir;
}

std::string dynamic_object::get_direction(){
	return direction_;
}

void dynamic_object::set_state(int state){
	state_ = state;
}


int dynamic_object::get_state(){
	return state_;
}

key_object::key_object(std::string s_id){
	id = std::stoi(s_id);
}

void key_object::print_object(){
	out.print_debug_object("K_");
}

std::string key_object::print_to_str(){
	std::string ret = std::string("K_") + std::to_string(id);
	return ret;
}

gate_object::gate_object(std::string s_id){
	id = std::stoi(s_id);
}

void gate_object::print_object(){
	out.print_debug_object("G_");
}

std::string gate_object::print_to_str(){
	std::string ret = std::string("G_") + std::to_string(id);
	return ret;
}

wall_object::wall_object(){

}

void wall_object::print_object(){
	out.print_debug_object("W_");
}

std::string wall_object::print_to_str(){
	std::string ret = std::string("w");
	return ret;
}

path_free::path_free(){

}

void path_free::print_object(){
	out.print_debug_object("__");
}

std::string path_free::print_to_str(){
	std::string ret = "";
	return ret;
}

player_object::player_object(std::string s_id){
	id = std::stoi(s_id);
}

void player_object::print_object(){
	out.print_debug_object("P_");
}



std::string player_object::print_to_str(){
	std::string ret = std::string("P_") + std::to_string(id);
	return ret;
}


keeper_object::keeper_object(std::string s_id){
	id = std::stoi(s_id);
}

void keeper_object::print_object(){
	out.print_debug_object("S_");
}


std::string keeper_object::print_to_str(){
	std::string ret = std::string("S_") + std::to_string(id);
	return ret;
}

finish_object::finish_object(){

}

void finish_object::print_object(){
	out.print_debug_object("F_");
}

std::string finish_object::print_to_str(){
	std::string ret = std::string("f");
	return ret;
}

create_player_object::create_player_object(std::string s_id){
	id = std::stoi(s_id);
}

void create_player_object::print_object(){
	out.print_debug_object("CP");
}

std::string create_player_object::print_to_str(){
	std::string ret = std::string("Cp_") + std::to_string(id);
	return ret;
}


void maze::set_player_direction(int x,int y,std::string dir){
	unsigned int i = x + y * width_;
	maze_array_.at(i)->set_direction(dir);
}

void maze::set_player_state(int x,int y,int state){
	unsigned int i = x + y * width_;
	maze_array_.at(i)->set_state(state);
}




int main(int argc, char* argv[]){
	out.set_debug(true);
	game game;
	try{
		maze maze;
		maze.set_maze("levels/level1.csv");
		game.set_maze(maze);
		maze.set_player_state(1,1,1);
		game.do_action();
		maze.print_maze();
	}catch (std::exception& error){
		std::cerr << "Exception: " << error.what() << std::endl;
	}


   	return 0;
}

// g++ maze.cpp output.cpp -std=c++11 -lboost_system -g 
