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


}

void maze::add_object(std::string value){
	maze_object_ptr obj_ptr;
	// std::cout << value << std::endl;
	if(value == ""){
		obj_ptr = std::make_shared<path_free>(path_free());
		// frees_.push_back(*(dynamic_cast<path_free_ptr*>(&obj_ptr)));
	}else if(value == "w"){
		obj_ptr = std::make_shared<wall_object>(wall_object());
		// walls_.push_back(obj_ptr);
	}else if(value == "f"){
		obj_ptr = std::make_shared<finish_object>(finish_object());
		// finishes_.push_back(obj_ptr);
	}else if(value.compare(0,2, "G_") == 0){
		obj_ptr = std::make_shared<gate_object>(gate_object(value.substr(2)));
		// gates_.push_back(obj_ptr);
	}else if(value.compare(0,2, "S_") == 0){
		obj_ptr = std::make_shared<keeper_object>(keeper_object(value.substr(2)));
		// keepers_.push_back(obj_ptr);
	}else if(value.compare(0,2, "K_") == 0){
		obj_ptr = std::make_shared<key_object>(key_object(value.substr(2)));
		// keys_.push_back(obj_ptr);
	}else if(value.compare(0,3, "Cp_") == 0){
		obj_ptr = std::make_shared<create_player_object>(create_player_object(value.substr(3)));
		// cps_.push_back(obj_ptr);
	}else{
		return;
	}
	maze_array_.push_back(obj_ptr);

}

maze::maze(std::string level){
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
				value = "";
			}else{
				value +=c;
			}
		} 

   	}
   	file.close();

   	print_maze();
}

maze_object::maze_object(){

}

static_object::static_object(){

}

dynamic_object::dynamic_object(){

}

key_object::key_object(std::string s_id){
	id = std::stoi(s_id);
}

void key_object::print_object(){
	out.print_debug_object("K_");
}

gate_object::gate_object(std::string s_id){
	id = std::stoi(s_id);
}

void gate_object::print_object(){
	out.print_debug_object("G_");
}

wall_object::wall_object(){

}

void wall_object::print_object(){
	out.print_debug_object("W_");
}

path_free::path_free(){

}

void path_free::print_object(){
	out.print_debug_object("__");
}

player_object::player_object(){

}

void player_object::print_object(){
	out.print_debug_object("P_");
}

keeper_object::keeper_object(std::string s_id){
	id = std::stoi(s_id);
}

void keeper_object::print_object(){
	out.print_debug_object("S_");
}

finish_object::finish_object(){

}

void finish_object::print_object(){
	out.print_debug_object("F_");
}

create_player_object::create_player_object(std::string s_id){
	id = std::stoi(s_id);
}

void create_player_object::print_object(){
	out.print_debug_object("CP");
}




int main(int argc, char* argv[]){
	out.set_debug(true);

	try{
		maze maze("levels/level1.csv");
	}catch (std::exception& error){
		std::cerr << "Exception: " << error.what() << std::endl;
	}


   	return 0;
}

// g++ maze.cpp output.cpp -std=c++11 -lboost_system -g 
