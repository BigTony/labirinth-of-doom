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
		int y = coords_counter_ / width_;
		int x = coords_counter_ - (y * width_);
		obj_ptr->set_x(x);
		obj_ptr->set_y(y);
		finishes_.push_back(obj_ptr);
	}else if(value.compare(0,2, "G_") == 0){
		obj_ptr = std::make_shared<gate_object>(gate_object(value.substr(2)));
		int y = coords_counter_ / width_;
		int x = coords_counter_ - (y * width_);
		obj_ptr->set_x(x);
		obj_ptr->set_y(y);
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
		int y = coords_counter_ / width_;
		int x = coords_counter_ - (y * width_);
		obj_ptr->set_x(x);
		obj_ptr->set_y(y);
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
		int y = coords_counter_ / width_;
		int x = coords_counter_ - (y * width_);
		obj_ptr->set_x(x);
		obj_ptr->set_y(y);
		cps_.push_back(obj_ptr);
		// free
		obj_ptr = std::make_shared<path_free>(path_free());
		frees_.push_back(obj_ptr);
		maze_array_.push_back(obj_ptr);
		return;
	}else{
		return;
	}
	maze_array_.push_back(obj_ptr);
}

maze::maze(std::string maze){
	srand (time(NULL));
	set_maze(maze);
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
			if((c == ',') || (c == '\n') || (!file.good())){
				add_object(value);
				coords_counter_++;
				value = "";
			}else{
				value +=c;
			}
   	}

   	file.close();
}

std::string maze::stop_go(){
	// hraci
	for (unsigned int i = 0; i < players_.size(); i++){
		if(players_.at(i)->get_state() == 1){
			check_collision(i);
		}
	}
	// keeper
	for (unsigned int i = 0; i <keepers_.size(); i++){
		if(keepers_.at(i)->get_state() == 1){
			check_collision_keeper(i);
		}
	}

	std::string ret = check_end();
	return ret;
}

void maze::set_direction_keeper(unsigned int keeper_id){
	int ran = rand() % 4;
	int x = keepers_.at(keeper_id)->get_x();
	int y = keepers_.at(keeper_id)->get_y();
	std::string dir = keepers_.at(keeper_id)->get_direction();
	if(ran == 0){
		if(dir != "north"){
			set_player_direction(x,y,"north");
		}else{
			set_player_direction(x,y,"south");
		}
	}else if(ran == 1){
		if(dir != "west"){
			set_player_direction(x,y,"west");
		}else{
			set_player_direction(x,y,"east");
		}
	}else if(ran == 2){
		if(dir != "south"){
			set_player_direction(x,y,"south");
		}else{
			set_player_direction(x,y,"north");
		}
	}else if(ran == 3){
		if(dir != "east"){
			set_player_direction(x,y,"east");
		}else{
			set_player_direction(x,y,"west");
		}
	}
}

void maze::check_collision_keeper(unsigned int keeper_id){
	std::string dir = keepers_.at(keeper_id)->get_direction();
	int x = keepers_.at(keeper_id)->get_x();
	int y = keepers_.at(keeper_id)->get_y();
	keepers_.at(keeper_id)->set_before_x(x);
	keepers_.at(keeper_id)->set_before_y(y);
	if((keepers_.at(keeper_id)->get_steps() % 5) == 0){
		set_direction_keeper(keeper_id);
	}
	if(dir == "north"){
		if(y != 0){
			if(maze_array_.at(x+((y-1)*width_))->print_to_str().compare(0,2,"G_") == 0){
				if((maze_array_.at(x+((y-1)*width_))->get_state()) == 1){
					y--;
					keepers_.at(keeper_id)->set_y(y);
					std::cout << "n:keeper" << std::endl;
					keepers_.at(keeper_id)->set_steps();
				}
				return;
			}
			if(maze_array_.at(x+((y-1)*width_))->print_to_str().compare(0,2,"S_") == 0){
				set_direction_keeper(keeper_id);
				return;
			}
			if(((maze_array_.at(x+((y-1)*width_))->print_to_str()) != "w") && (maze_array_.at(x+((y-1)*width_))->print_to_str().compare(0,2,"K_") != 0)){
				y--;
				keepers_.at(keeper_id)->set_y(y);
				std::cout << "n:keeper" << std::endl;
				keepers_.at(keeper_id)->set_steps();
			}else{
				set_direction_keeper(keeper_id);
			}
		}		
	}else if(dir == "west"){
		if(x != 0){
			if(maze_array_.at(x-1+(y*width_))->print_to_str().compare(0,2,"G_") == 0){
				if((maze_array_.at(x-1+(y*width_))->get_state()) == 1){
					x--;
					keepers_.at(keeper_id)->set_x(x);
					std::cout << "w:keeper" << std::endl;
					keepers_.at(keeper_id)->set_steps();
				}
				return;
			}
			if(maze_array_.at(x-1+(y*width_))->print_to_str().compare(0,2,"S_") == 0){
				set_direction_keeper(keeper_id);
				return;
			}
			if(((maze_array_.at(x-1+(y*width_))->print_to_str()) != "w") && (maze_array_.at(x-1+(y*width_))->print_to_str().compare(0,2,"K_") != 0)){
				x--;
				keepers_.at(keeper_id)->set_x(x);
				std::cout << "w:keeper" << std::endl;
				keepers_.at(keeper_id)->set_steps();
			}else{
				set_direction_keeper(keeper_id);
			}

		}
	}else if(dir == "south"){
		if(y != length_-1){
			if(maze_array_.at(x+((y+1)*width_))->print_to_str().compare(0,2,"G_") == 0){
				if((maze_array_.at(x+((y+1)*width_))->get_state()) == 1){
					y++;
					keepers_.at(keeper_id)->set_y(y);
					std::cout << "s" << std::endl;
					keepers_.at(keeper_id)->set_steps();
				}
				return;
			}
			if(maze_array_.at(x+((y+1)*width_))->print_to_str().compare(0,2,"S_") == 0){
				set_direction_keeper(keeper_id);
				return;
			}
			if(((maze_array_.at(x+((y+1)*width_))->print_to_str()) != "w")&&(maze_array_.at(x+((y+1)*width_))->print_to_str().compare(0,2,"K_") != 0)){
				y++;
				keepers_.at(keeper_id)->set_y(y);
				std::cout << "s" << std::endl;
				keepers_.at(keeper_id)->set_steps();
			}else{
				set_direction_keeper(keeper_id);
			}
		}else{
			set_direction_keeper(keeper_id);
		}
	}else if(dir == "east"){
		if(x != width_-1){
			if(maze_array_.at(x+1+(y*width_))->print_to_str().compare(0,2,"G_") == 0){
				if((maze_array_.at(x+1+(y*width_))->get_state()) == 1){
					x++;
					keepers_.at(keeper_id)->set_x(x);
					std::cout << "e" << std::endl;
					keepers_.at(keeper_id)->set_steps();
					return;
				}
			}
			if(maze_array_.at(x+1+(y*width_))->print_to_str().compare(0,2,"S_") == 0){
				set_direction_keeper(keeper_id);
				return;
			}
			if(((maze_array_.at(x+1+(y*width_))->print_to_str()) != "w")&&(maze_array_.at(x+1+(y*width_))->print_to_str().compare(0,2,"K_") != 0)){
				x++;
				keepers_.at(keeper_id)->set_x(x);
				std::cout << "e" << std::endl;
				keepers_.at(keeper_id)->set_steps();
			}else{
				set_direction_keeper(keeper_id);
			}	
		}else{
			set_direction_keeper(keeper_id);
		}
	}
}

std::string maze::check_end(){
	std::string message;
	for (unsigned int i = 0; i < players_.size(); i++){
		if(players_.at(i)->get_state() == 1){
			message.append(move_one(i));
		}
	}
	

	for (unsigned int i = 0; i < keepers_.size(); i++){
		if(keepers_.at(i)->get_state() == 1){
			message.append(move_one_keeper(i));
		}
	}
	return message;
} 

std::string maze::move_one_keeper(unsigned int keeper_id){
	int x = keepers_.at(keeper_id)->get_x();
	int y = keepers_.at(keeper_id)->get_y();
	for (unsigned int i = 0; i < keepers_.size(); i++){
		// hraci na stejnem policku
		if((keepers_.at(i)->get_x() == x) && (keepers_.at(i)->get_y() == y) && (i != keeper_id)){
			// move_one(i);
			if(keepers_.at(i)->get_state() == 0){
				keepers_.at(keeper_id)->set_x(keepers_.at(keeper_id)->get_before_x());
				keepers_.at(keeper_id)->set_y(keepers_.at(keeper_id)->get_before_y());
				return "";
			}else{
				keepers_.at(keeper_id)->set_x(keepers_.at(keeper_id)->get_before_x());
				keepers_.at(keeper_id)->set_y(keepers_.at(keeper_id)->get_before_y());
				for (unsigned int c = i; c < players_.size(); c++){
					if((keepers_.at(c)->get_x() == x) && (keepers_.at(c)->get_y() == y) && (c != keeper_id)){
						keepers_.at(c)->set_x(keepers_.at(c)->get_before_x());
						keepers_.at(c)->set_y(keepers_.at(c)->get_before_y());
					}
				}
				return "";
			}
		}
	}
	int before = keepers_.at(keeper_id)->get_before_x() + (keepers_.at(keeper_id)->get_before_y() * width_);
	maze_object_ptr obj_ptr;
	obj_ptr = maze_array_.at(before);
	maze_array_.at(before) = maze_array_.at(x+(y*width_));
	maze_array_.at(x+(y*width_)) = obj_ptr;
	// before
	std::string ret = std::string(std::to_string(keepers_.at(keeper_id)->get_before_x())) + "," +  std::string(std::to_string(keepers_.at(keeper_id)->get_before_y()));
	// actual
	ret.append(" " + std::string(std::to_string(keepers_.at(keeper_id)->get_x())) + "," +  std::string(std::to_string(keepers_.at(keeper_id)->get_y())) + "," + keepers_.at(keeper_id)->print_to_str() + "," + keepers_.at(keeper_id)->get_direction() + " ");
	return ret;
}


std::string maze::move_one(unsigned int player_id){
	int x = players_.at(player_id)->get_x();
	int y = players_.at(player_id)->get_y();

	// std::cout << "player: " << "x: " << x << " " << "y: " << y << std::endl;

	// projdu hrace
	for (unsigned int i = 0; i < players_.size(); i++){
		// hraci na stejnem policku
		if((players_.at(i)->get_x() == x) && (players_.at(i)->get_y() == y) && (i != player_id)){
			// move_one(i);
			if(players_.at(i)->get_state() == 0){
				players_.at(player_id)->set_x(players_.at(player_id)->get_before_x());
				players_.at(player_id)->set_y(players_.at(player_id)->get_before_y());
				return "";
			}else{
				players_.at(player_id)->set_x(players_.at(player_id)->get_before_x());
				players_.at(player_id)->set_y(players_.at(player_id)->get_before_y());
				for (unsigned int c = i; c < players_.size(); c++){
					if((players_.at(c)->get_x() == x) && (players_.at(c)->get_y() == y) && (c != player_id)){
						players_.at(c)->set_x(players_.at(c)->get_before_x());
						players_.at(c)->set_y(players_.at(c)->get_before_y());
					}
				}
				return "";
			}
		}

	}
	// keepers
	for (unsigned int i = 0; i < keepers_.size(); i++){
		// hraci na stejnem policku
		// std::cout << "keeper: " << "x: " << keepers_.at(i)->get_x() << " " << "y: " << keepers_.at(i)->get_y() << std::endl;
		if((keepers_.at(i)->get_before_x() == x) && (keepers_.at(i)->get_before_y() == y)){
			// move_one(i);
			// int x_b = players_.at(player_id)->get_before_x();
			// int y_b = players_.at(player_id)->get_before_y();
			// std::string playerid = maze_array_.at(x+(y*width_))->print_to_str();
			// int p_id = std::stoi(playerid.substr(2));
			// for (unsigned int i = 0; i < cps_.size(); i++){
			// 	std::string createp_id = cps_.at(i)->print_to_str();
			// 	int cp_id = std::stoi(createp_id.substr(3));
			// 	if(cp_id == p_id){
			// 		//
			// 	}
			// }
			
			
			players_.at(player_id)->set_x(3);
			players_.at(player_id)->set_y(3);
			maze_array_.at(3+(3*width_)) = players_.at(player_id);
			int before = players_.at(player_id)->get_before_x() + (players_.at(player_id)->get_before_y() * width_);
			maze_object_ptr obj_ptr;
			obj_ptr = std::make_shared<path_free>(path_free());
			maze_array_.at(before) = obj_ptr;
			std::string ret = std::string(std::to_string(players_.at(player_id)->get_before_x())) + "," +  std::string(std::to_string(players_.at(player_id)->get_before_y()));
			ret.append(" " + std::string(std::to_string(players_.at(player_id)->get_x())) + "," +  std::string(std::to_string(players_.at(player_id)->get_y())) + "," + players_.at(player_id)->print_to_str() + "," + players_.at(player_id)->get_direction() + " " );
			return ret;
			// maze_array_.at(x+(y*width_)) = obj_ptr;
		}
	}
	int before = players_.at(player_id)->get_before_x() + (players_.at(player_id)->get_before_y() * width_);
	maze_object_ptr obj_ptr;
	obj_ptr = maze_array_.at(before);
	maze_array_.at(before) = maze_array_.at(x+(y*width_));
	maze_array_.at(x+(y*width_)) = obj_ptr;
	// before
	std::string ret = std::string(std::to_string(players_.at(player_id)->get_before_x())) + "," +  std::string(std::to_string(players_.at(player_id)->get_before_y()));
	// actual
	ret.append(" " + std::string(std::to_string(players_.at(player_id)->get_x())) + "," +  std::string(std::to_string(players_.at(player_id)->get_y())) + "," + players_.at(player_id)->print_to_str() + "," + players_.at(player_id)->get_direction() + " " );
	return ret;
}

void maze::check_collision(unsigned int player_id){
	std::string dir = players_.at(player_id)->get_direction();
	int x = players_.at(player_id)->get_x();
	int y = players_.at(player_id)->get_y();
	players_.at(player_id)->set_before_x(x);
	players_.at(player_id)->set_before_y(y);
	std::cout << "player: x: " << x << " " << "y: " << y << std::endl;
	if(dir == "north"){
		if(y != 0){
			if(maze_array_.at(x+((y-1)*width_))->print_to_str() == "f"){
				std::cout << "pocet kroku: " << players_.at(player_id)->get_steps() << std::endl;
			}
			if(maze_array_.at(x+((y-1)*width_))->print_to_str().compare(0,2,"G_") == 0){
				if((maze_array_.at(x+((y-1)*width_))->get_state()) == 1){
					y--;
					players_.at(player_id)->set_y(y);
					players_.at(player_id)->set_steps();
					std::cout << "n" << std::endl;
				}
				return;
			}
			if(((maze_array_.at(x+((y-1)*width_))->print_to_str()) != "w")&&(maze_array_.at(x+((y-1)*width_))->print_to_str().compare(0,2,"K_") != 0)){
				y--;
				players_.at(player_id)->set_y(y);
				players_.at(player_id)->set_steps();
				std::cout << "n" << std::endl;
			}
		}		
	}else if(dir == "west"){
		if(x != 0){
			if(maze_array_.at(x+-1+(y*width_))->print_to_str() == "f"){
				std::cout << "pocet kroku: " << players_.at(player_id)->get_steps() << std::endl;
			}
			if(maze_array_.at(x-1+(y*width_))->print_to_str().compare(0,2,"G_") == 0){
				if((maze_array_.at(x-1+(y*width_))->get_state()) == 1){
					x--;
					players_.at(player_id)->set_x(x);
					players_.at(player_id)->set_steps();
					std::cout << "w" << std::endl;
				}
				return;
			}
			if(((maze_array_.at(x-1+(y*width_))->print_to_str()) != "w")&&(maze_array_.at(x-1+(y*width_))->print_to_str().compare(0,2,"K_") != 0)){
				x--;
				players_.at(player_id)->set_x(x);
				players_.at(player_id)->set_steps();
				std::cout << "w" << std::endl;
			}	
		}
	}else if(dir == "south"){
		if(y != length_-1){
			if(maze_array_.at(x+((y+1)*width_))->print_to_str() == "f"){
				std::cout << "pocet kroku: " << players_.at(player_id)->get_steps() << std::endl;
			}
			if(maze_array_.at(x+((y+1)*width_))->print_to_str().compare(0,2,"G_") == 0){
				if((maze_array_.at(x+((y+1)*width_))->get_state()) == 1){
					y++;
					players_.at(player_id)->set_y(y);
					players_.at(player_id)->set_steps();
					std::cout << "s" << std::endl;
				}
				return;
			}
			if(((maze_array_.at(x+((y+1)*width_))->print_to_str()) != "w")&&(maze_array_.at(x+((y+1)*width_))->print_to_str().compare(0,2,"K_") != 0)){
				y++;
				players_.at(player_id)->set_y(y);
				players_.at(player_id)->set_steps();
				std::cout << "s" << std::endl;
			}
		}
	}else if(dir == "east"){
		if(x != width_-1){
			if(maze_array_.at(x+1+(y*width_))->print_to_str() == "f"){
				std::cout << "pocet kroku: " << players_.at(player_id)->get_steps() << std::endl;
			}
			if(maze_array_.at(x+1+(y*width_))->print_to_str().compare(0,2,"G_") == 0){
				if((maze_array_.at(x+1+(y*width_))->get_state()) == 1){
					x++;
					players_.at(player_id)->set_x(x);
					players_.at(player_id)->set_steps();
					std::cout << "e" << std::endl;
				}
				return;
			}
			if(((maze_array_.at(x+1+(y*width_))->print_to_str()) != "w")&&(maze_array_.at(x+1+(y*width_))->print_to_str().compare(0,2,"K_") != 0)){
				x++;
				players_.at(player_id)->set_x(x);
				players_.at(player_id)->set_steps();
				std::cout << "e" << std::endl;
			}	
		}
	}
}

game::game(int client_id,std::string maze):maze_(maze){
	owner_id_=client_id;
}


std::string game::do_action(){	
	std::string ret = maze_.stop_go();
	return ret;
}

void game::set_maze(maze maze){
	maze_ = maze;
}



maze_object::maze_object(){

}

std::string maze_object::print_to_str(){
	return "O";
}

int maze_object::get_steps(){
	return 0;
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

int maze_object::get_id(){
	return id;
}

void dynamic_object::pick_key(unsigned int key_id){
	// int x = players_.at(player_id)->get_x();
	// int y = players_.at(player_id)->get_x();
	// if(maze_array_.at(x+(y*width_))->print_to_str().compare(0,2,"G_") == 0){
	// keys_.push_back(maze_array_.at(key_id);
}


std::string maze::pick_key(int x,int y){
	// int x = players_.at(player_id)->get_x();
	// int y = players_.at(player_id)->get_x();
	std::string ret = "";
	unsigned int player_id;
	for (unsigned int i = 0; i < players_.size(); i++){
		if((players_.at(i)->get_x() == x) && (players_.at(i)->get_y() == y)){
			player_id = i;
			break;
		}
	}
	std::string dir = players_.at(player_id)->get_direction();
	if(dir == "north"){
		if(maze_array_.at(x+((y-1)*width_))->print_to_str().compare(0,2,"K_") == 0){
			players_.at(player_id)->keys_.push_back(maze_array_.at(x+((y+1)*width_)));
			maze_object_ptr obj_ptr;
			obj_ptr = std::make_shared<path_free>(path_free());
			maze_array_.at(x+((y-1)*width_)) = obj_ptr;
			players_.at(player_id)->set_steps();

			ret.append(std::string(std::to_string(x)) + "," +  std::string(std::to_string(y-1)) + " ");
		}
	}else if(dir == "west"){
		if(maze_array_.at(x-1+(y*width_))->print_to_str().compare(0,2,"K_") == 0){
			players_.at(player_id)->keys_.push_back(maze_array_.at(x-1+(y*width_)));
			maze_object_ptr obj_ptr;
			obj_ptr = std::make_shared<path_free>(path_free());
			maze_array_.at(x-1+(y*width_)) = obj_ptr;
			players_.at(player_id)->set_steps();
			ret.append(std::string(std::to_string(x-1)) + "," +  std::string(std::to_string(y)) + " ");
		}
	}else if(dir == "south"){
		if(maze_array_.at(x+((y+1)*width_))->print_to_str().compare(0,2,"K_") == 0){
			players_.at(player_id)->keys_.push_back(maze_array_.at(x+((y+1)*width_)));
			maze_object_ptr obj_ptr;
			obj_ptr = std::make_shared<path_free>(path_free());
			maze_array_.at(x+((y+1)*width_)) = obj_ptr;
			players_.at(player_id)->set_steps();
			ret.append(std::string(std::to_string(x)) + "," +  std::string(std::to_string(y+1)) + " ");
		}
	}else if(dir == "east"){
		if(maze_array_.at(x+1+(y*width_))->print_to_str().compare(0,2,"K_") == 0){
			players_.at(player_id)->keys_.push_back(maze_array_.at(x+1+(y*width_)));
			maze_object_ptr obj_ptr;
			obj_ptr = std::make_shared<path_free>(path_free());
			maze_array_.at(x+1+(y*width_)) = obj_ptr;
			players_.at(player_id)->set_steps();
			ret.append(std::string(std::to_string(x+1)) + "," +  std::string(std::to_string(y)) + " ");
		}
	}
	return ret;
}

std::string maze::open_gate(int x,int y){
	// int x = players_.at(player_id)->get_x();
	// int y = players_.at(player_id)->get_x();
	std::string ret = "";
	unsigned int player_id;
	for (unsigned int i = 0; i < players_.size(); i++){
		if((players_.at(i)->get_x() == x) && (players_.at(i)->get_y() == y)){
			player_id = i;
			break;
		}
	}
	std::string dir = players_.at(player_id)->get_direction();
	if(dir == "north"){		
		if(maze_array_.at(x+((y-1)*width_))->print_to_str().compare(0,2,"G_") == 0){
			std::string gate_id = maze_array_.at(x+((y-1)*width_))->print_to_str();
			int g_id = std::stoi(gate_id.substr(2));
			for (unsigned int i = 0; i < players_.at(player_id)->keys_.size(); i++){
				std::string key_id = players_.at(player_id)->keys_.at(i)->print_to_str();
				int k_id = std::stoi(key_id.substr(2));
				if(k_id == g_id){
					maze_object_ptr obj_ptr;
					obj_ptr = std::make_shared<path_free>(path_free());
					maze_array_.at(x+((y-1)*width_)) =  obj_ptr;
					players_.at(player_id)->set_steps();
					ret.append(std::string(std::to_string(x)) + "," +  std::string(std::to_string(y-1)) + " ");
				}
			}
		}
	}else if(dir == "west"){
		if(maze_array_.at(x-1+(y*width_))->print_to_str().compare(0,2,"G_") == 0){
			std::string gate_id = maze_array_.at(x-1+(y*width_))->print_to_str();
			int g_id = std::stoi(gate_id.substr(2));
			for (unsigned int i = 0; i < players_.at(player_id)->keys_.size(); i++){
				std::string key_id = players_.at(player_id)->keys_.at(i)->print_to_str();
				int k_id = std::stoi(key_id.substr(2));
				if(k_id == g_id){
					maze_object_ptr obj_ptr;
					obj_ptr = std::make_shared<path_free>(path_free());
					maze_array_.at(x-1+(y*width_)) =  obj_ptr;
					players_.at(player_id)->set_steps();
					ret.append(std::string(std::to_string(x-1)) + "," +  std::string(std::to_string(y)) + " ");
				}
			}
		}
	}else if(dir == "south"){
		if(maze_array_.at(x+((y+1)*width_))->print_to_str().compare(0,2,"G_") == 0){
			std::string gate_id = maze_array_.at(x+((y+1)*width_))->print_to_str();
			int g_id = std::stoi(gate_id.substr(2));
			for (unsigned int i = 0; i < players_.at(player_id)->keys_.size(); i++){
				std::string key_id = players_.at(player_id)->keys_.at(i)->print_to_str();
				int k_id = std::stoi(key_id.substr(2));
				if(k_id == g_id){
					maze_object_ptr obj_ptr;
					obj_ptr = std::make_shared<path_free>(path_free());
					maze_array_.at(x+((y+1)*width_)) =  obj_ptr;
					players_.at(player_id)->set_steps();
					ret.append(std::string(std::to_string(x)) + "," +  std::string(std::to_string(y+1)) + " ");
				}
			}
		}
	}else if(dir == "east"){
		if(maze_array_.at(x+1+(y*width_))->print_to_str().compare(0,2,"G_") == 0){
			std::string gate_id = maze_array_.at(x+1+(y*width_))->print_to_str();
			int g_id = std::stoi(gate_id.substr(2));
			for (unsigned int i = 0; i < players_.at(player_id)->keys_.size(); i++){
				std::string key_id = players_.at(player_id)->keys_.at(i)->print_to_str();
				int k_id = std::stoi(key_id.substr(2));
				if(k_id == g_id){
					maze_object_ptr obj_ptr;
					obj_ptr = std::make_shared<path_free>(path_free());
					maze_array_.at(x+1+(y*width_)) =  obj_ptr;
					players_.at(player_id)->set_steps();
					ret.append(std::string(std::to_string(x+1)) + "," +  std::string(std::to_string(y)) + " ");
				}
			}
		}
	}
	return ret;
}

static_object::static_object(){

}

dynamic_object::dynamic_object(){

}

int maze_object::get_before_x(){
	return before_x_;
}

int maze_object::get_before_y(){
	return before_y_;
}

void maze_object::set_before_x(int before){
	before_x_ = before;
}

void maze_object::set_before_y(int before){
	before_y_ = before;
}

void maze_object::set_direction(std::string dir){
	direction_ = dir;
}

std::string maze_object::get_direction(){
	return direction_;
}

void maze_object::set_state(int state){
	state_ = state;
}


int maze_object::get_state(){
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
	if(get_direction() == "north"){
		out.print_debug_object("^_");
	}else if(get_direction() == "west"){
		out.print_debug_object("<_");
	}else if(get_direction() == "south"){
		out.print_debug_object("v_");
	}else if(get_direction() == "east"){
		out.print_debug_object(">_");
	}
}



std::string player_object::print_to_str(){
	std::string ret = std::string("P_") + std::to_string(id);
	return ret;
}

int player_object::get_steps(){
	return steps_;
}

void player_object::set_steps(){
	steps_++;
}


keeper_object::keeper_object(std::string s_id){
	id = std::stoi(s_id);
	set_state(1);
}

void keeper_object::print_object(){
	out.print_debug_object("S_");
}


std::string keeper_object::print_to_str(){
	std::string ret = std::string("S_") + std::to_string(id);
	return ret;
}

int keeper_object::get_steps(){
	return steps_;
}

void keeper_object::set_steps(){
	steps_++;
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
	// maze_array_.at(i)->print_object();
	maze_array_.at(i)->set_state(state);
	// std::cout << "state: " << maze_array_.at(i)->get_state() << std::endl;
}


client_maze::client_maze(std::string maze){
	int counter = 0;
	std::string value = "";
	// width
	while(maze[counter] != '\n'){
		value += maze[counter];
		counter++;
	}
	width_ = std::stoi(value);
	value = "";
	counter++;
	// length
	while(maze[counter] != '\n'){
		value += maze[counter];
		counter++;
	}
	length_ = std::stoi(value);
	value = "";
	counter++;
	counter++;

	while ( maze[counter] != EOF ){
		if(( maze[counter] == ',') || (maze[counter] == '\n')){
			add_object(value);
			coords_counter_++;
			counter++;
			value = "";
		}else{
			value += maze[counter];
			counter++;
		}
   	}
}

void maze::check_key(){
	for (unsigned int i = 0; i < keys_.size(); i++){
		std::cout << keys_.at(i)->get_x() << " " << keys_.at(i)->get_y() << std::endl;
	}
}

void maze::check_gate(){
	for (unsigned int i = 0; i < gates_.size(); i++){
		std::cout << gates_.at(i)->get_x() << " " << gates_.at(i)->get_y() << std::endl;
	}
}

void maze::check_steps(int x,int y){
	unsigned int player_id;
	for (unsigned int i = 0; i < players_.size(); i++){
		if((players_.at(i)->get_x() == x) && (players_.at(i)->get_y() == y)){
			player_id = i;
			break;
		}
	}
	std::cout << "pocet kroku: " << players_.at(player_id)->get_steps() << std::endl;
}

void game::terminal_command(){
	maze_.print_maze();
    std::string command_=in.wait_cmd();
    int x = maze_.players_.at(0)->get_x();
    int y = maze_.players_.at(0)->get_y();
    // maze_.set_player_state(4,1,1);
    // maze_.set_player_direction(4,1,"west");
    // maze_.set_player_state(2,3,1);
    // maze_.set_player_direction(2,3,"north");
    std::string message;
    message.append("send_game_change ");
    if (command_.compare("w")==0){
    	maze_.set_player_direction(x,y,"north");
    }else if(command_.compare("a")==0){
    	maze_.set_player_direction(x,y,"west");
    }else if(command_.compare("s")==0){
    	maze_.set_player_direction(x,y,"south");
    }else if(command_.compare("d")==0){
    	maze_.set_player_direction(x,y,"east");
    }else if(command_.compare("go")==0){
    	maze_.set_player_state(x,y,1);
    }else if(command_.compare("stop")==0){
    	maze_.set_player_state(x,y,0);
    }else if(command_.compare("pick")==0){
    	message.append(maze_.pick_key(x,y));
    }else if(command_.compare("open")==0){
    	message.append(maze_.open_gate(x,y));
    }else if(command_.compare("checkk")==0){
    	maze_.check_key();
    }else if(command_.compare("checkg")==0){
    	maze_.check_gate();
    }else if(command_.compare("steps")==0){
    	maze_.check_steps(x,y);
    }
    message.append(do_action());
    std::cout << message << std::endl;
    terminal_command();
}

void maze::add_player(int i){
	maze_object_ptr obj_ptr;
	obj_ptr = std::make_shared<player_object>(player_object(std::to_string(i)));
	// for (i = 0; i < cps_.size(); i++){
	// 	int x = cps_.at(i)->get_x();
	// 	int y = cps_.at(i)->get_y();
	// 	std::string cp_id = maze_array_.at(x+(y*width_))->print_to_str();
	// 	int c_id = std::stoi(cp_id.substr(3));
	// 	if(players_.at(i) == nullptr){
	// 		players_.at(i) = obj_ptr;
	// 		break;
	// 	}
	// }
	int x = 3;
	int y = 3;
	obj_ptr->set_x(x);
	obj_ptr->set_y(y);
	players_.push_back(obj_ptr);
	maze_array_.at(x+(y*width_)) = obj_ptr;
	// int y = coords_counter_ / width_;
	// int x = coords_counter_ - (y * width_);
	// obj_ptr->set_x(x);
	// obj_ptr->set_y(y);
	// players_.push_back(obj_ptr);
	// players_.at() = 
}

void game::add_player(client_connection_ptr ptr){
	unsigned int i = 0;
	for (i = 0; i < players_id_.size(); i++){
		if(players_id_.at(i) == nullptr){
			players_id_.at(i) = ptr;
			break;
		}
	}
	maze_.add_player(i);
}

// int main(int argc, char* argv[]){
// 	out.set_debug(true);
// 	game game(0,"levels/level1.csv");
// 	client_connection_ptr ptr;
// 	game.add_player(ptr);
// 	game.terminal_command();
// 	// client_maze cmaze(game.maze_.msg_send_maze());
// 	// cmaze.print_maze();
// 
//    	return 0;
// }



// g++ maze.cpp output.cpp -std=c++11 -lboost_system -g 
