// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// parser.cpp

#include "parser.hpp"

#define MAX_SIZE	15

void parser_client::parse_arguments(std::string message){
	if(message.compare(0,9, "send_maze") == 0){
		int i = 10;
		std::string active;
		// nacte souradnice
		while(i < 15){
			if(message[i] == ' '){
				y = std::stoi(active);
				break;
			}
			if(message[i] == 'x'){
				x = std::stoi(active);
				active = "";
				i++;
				continue;
			}
			active += message[i];
			i++;
		}
		// nacte bludiste
		message.erase(0,i+1);
		maze = message;
	}else if(message.compare(0,16, "send_game_change") == 0){
		std::cout << "start" << std::endl;
		int i = 17;
		std::string active;
		int space = 0;
		// send_game_change OBJ XxY OBJ....
		while(i < message.length()){
			if(isalpha(message[i])){
				// sudej pocet mezer
				if(space % 2 == 0){
					active += message[i];
				}else{	
					std::cout << "sour x: " << active << std::endl;
					active = "";
				}
			}else if(isdigit(message[i])){
				active += message[i];
			}else if(message[i] == ' '){
				// sudej pocet mezer
				if(space % 2 == 0){
					std::cout << "obj: " << active << std::endl;
					active = "";
				}else{
					std::cout << "sour y: " << active << std::endl;
					active = "";
				}
				space++;
				
			}
			i++;
		}
		std::cout << "sour y: " << active << std::endl;
	}else if(message.compare(0,10, "send_lobby") == 0){
		int i = 11;
		std::string game_name,maze_name,player_count,game_num;
		int comma = 0;
		while(i < message.length()){
			if(message[i] == ' '){
				comma = 0;
				std::cout << game_name << " " << maze_name << " " << player_count << " " << game_num << std::endl;
				game_name,maze_name,player_count,game_num = "";
			}else if(message[i] == '-'){
				comma++;
				i++;
			}

			if(comma == 0){
				game_name += message[i];
			}else if(comma == 1){
				maze_name += message[i];
			}else if(comma == 2){
				player_count += message[i];
			}else if(comma == 3){
				game_num += message[i];
			}
			i++;
		}
		std::cout << game_name << " " << maze_name << " " << player_count << " " << game_num << std::endl;
	}else if(message.compare(0,10, "send_stats") == 0){
		int i = 11;
		int comma = 0;
		std::string steps,game_time;
		while(i < message.length()){
			if(message[i] == ' '){
				comma = 0;
				std::cout << steps << " " << game_time << std::endl;
				steps,game_time = "";
			}else if(message[i] == '-'){
				comma++;
				i++;
			}
		}
	}else{
		// error
	}
}

int parser_client::getx(){
	return x;
}

int parser_client::gety(){
	return y;
}

std::string parser_client::getmaze(){
	return maze;
}

void parser_server::parse_arguments(std::string message){
	if(message.compare(0,8, "send_cmd") == 0){
		if(message.compare(9,13, "open") == 0){
			std::cout << "open" << std::endl;
		}else if(message.compare(9,11, "go") == 0){
			std::cout << "go" << std::endl;
		}else if(message.compare(9,13, "stop") == 0){
			std::cout << "stop" << std::endl;
		}else if(message.compare(9,13, "left") == 0){
			std::cout << "left" << std::endl;
		}else if(message.compare(9,13, "right") == 0){
			std::cout << "right" << std::endl;
		}else if(message.compare(9,13, "take") == 0){
			std::cout << "take" << std::endl;
		}else{
			// spatny prikaz
		}
	}else if(message.compare(0,15, "send_get_lobbys") == 0){
		std::cout << "client zada o lobby" << std::endl;
	}else if(message.compare(0,4, "join") == 0){
		int i = 5;
		std::string number;
		while(i < message.length()){
			number += message[i];
			i++;
		}
		int join_number = std::stoi(number);
		std::cout << join_number << std::endl;
	}else if(message.compare(0,10, "disconnect") == 0){
		std::cout << "client provedl disconnect" << std::endl;
	}else if(message.compare(0,4, "exit") == 0){
		std::cout << "client provedl exit" << std::endl;
	}else if(message.compare(0,6, "create") == 0){
		int comma = 0;
		int i = 7;
		std::string game_name,maze_name,tik_tak;
		while(i < message.length()){
			if(message[i] == '-'){
				comma++;
				i++;
			}
			if(comma == 0){
				game_name += message[i];
			}else if(comma == 1){
				maze_name += message[i];
			}else if(comma == 2){
				tik_tak += message[i];
			}
			i++;
		}
		std::cout << game_name << " " << maze_name << " " << tik_tak << std::endl;
	}else if(message.compare(0,2, "gm") == 0){
		if(message.compare(3,8, "start") == 0){
			std::cou t << "gm client: start" << std::endl;
		}else if(message.compare(3,10, "restart") == 0){
			std::cout << "gm client: restart" << std::endl;
		}else if(message.compare(3,7, "stop") == 0){
			std::cout << "gm client: stop" << std::endl;
		}else if(message.compare(3,7, "kick") == 0){
			std::cout << "gm client: kick #asi tu pak bude num zatim neresim" << std::endl;
		}else{
			// spatny gm prikaz
		}
	}else{
		// error
	}
}

// int main(int argc, char* argv[]){
// 	parser_server parser;
// 	parser.parse_arguments("create suprhra-epicmaze-0.5");
// 	return 0;
// }