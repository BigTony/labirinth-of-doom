// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// maze.cpp

#include "maze.hpp"
#include "output.hpp"

void maze::add_object(std::string value){
	// std::cout << value << std::endl;
	if(value == ""){
		maze_array_.emplace_back(path_free());
		// out_print_debug_object(" \t")
	}else if(value == "w"){
		maze_array_.emplace_back(wall_object());
		// out_print_debug_object("w\t")
	}else if(value == "f"){
		maze_array_.emplace_back(finish_object());
		// out_print_debug_object("f\t")
	}else if(value.compare(0,2, "G_") == 0){
		maze_array_.emplace_back(gate_object(value.substr(2)));
		// out_print_debug_object("G\t")
	}else if(value.compare(0,2, "S_") == 0){
		maze_array_.emplace_back(keeper_object(value.substr(2)));
		// out_print_debug_object("G\t")
	}else if(value.compare(0,2, "K_") == 0){
		maze_array_.emplace_back(key_object(value.substr(2)));
		// out_print_debug_object("G\t")
	}else if(value.compare(0,3, "Cp_") == 0){
		maze_array_.emplace_back(create_player_object(value.substr(3)));
		// out_print_debug_object("G\t")
	}else{
		// out_print_error("EERR");
	}
}

maze::maze(std::string level){
	std::ifstream file ( level ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	std::string value = "";
	while ( file.good() ){
    	char c = file.get();
		if (file.good()){
			if(c == ','){
				add_object(value);
				value = "";
			}else{
				value +=c;
			}
		}   		
   	}
   	file.close();
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

gate_object::gate_object(std::string s_id){
	id = std::stoi(s_id);
}

wall_object::wall_object(){

}

path_free::path_free(){

}

player_object::player_object(){

}

keeper_object::keeper_object(std::string s_id){
	id = std::stoi(s_id);
}

finish_object::finish_object(){

}

create_player_object::create_player_object(std::string s_id){
	id = std::stoi(s_id);
}




int main(int argc, char* argv[]){
	

	maze maze("levels/level1.csv");


   	return 0;
}

    
