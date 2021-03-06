#include "client_connect.hpp"

using boost::asio::ip::tcp;


server_connection::server_connection(boost::asio::io_service* io,tcp::resolver::iterator endpoint_iterator):socket_(*io),mutex_wait_msg_(1),mutex_msg_recived_(0){
	clout.print_debug("Creating server connection");
	io_=io;
	connect(endpoint_iterator);
}

void server_connection::check_socket(){
	clout.print_debug("Socket to server is "+ std::to_string(socket_.is_open()));
}

void server_connection::send_msg(std::string message){
	clout.print_debug(std::string("Sending msg to server, socket to server is")+ std::to_string(socket_.is_open()));
	msg_quee_.push_back(message);
	if (msg_quee_.size()==1){
		while (!(msg_quee_.empty())){
			send_quee_msg(msg_quee_.back());
			msg_quee_.pop_back();
		}
	}
}

void server_connection::send_quee_msg(std::string message){
	if (message.length()>MAX_MSG_LENGTH) {
		clout.print_warn("Msg is too long for transmit");
		return;
	}
	char header[HEADER_LENGTH+1];
	std::sprintf(header, "%5d", message.length());
	send_data_=header+message;
	std::cout << send_data_ << std::endl;
	boost::asio::async_write(socket_, boost::asio::buffer(send_data_.data(),send_data_.length()),[this](boost::system::error_code error, std::size_t){
		if (!error){
			clout.print_debug("Msg was send");
		}
		else{
			clout.print_error("Unable send msg. Server hang out unexpectly");
			status_=CONNECTION_LOST;
			socket_.close();
		}
	});
}

void server_connection::wait_msg(){
	clout.print_debug(std::string("Waiting msg from server,socket to server is")+ std::to_string(socket_.is_open()));
	boost::asio::async_read(socket_,boost::asio::buffer(header_, HEADER_LENGTH),[this](boost::system::error_code error, std::size_t length){
		if (!error){
			char header[HEADER_LENGTH + 1] = "";
			std::strncat(header, header_, HEADER_LENGTH);
			recived_ = std::atoi(header);
			clout.print_debug(std::string("Recived header:\t")+header_);
			boost::asio::async_read(socket_,boost::asio::buffer(data_, recived_),[this](boost::system::error_code error, std::size_t length){
				if (!error){
					data_[recived_]='\0';
					recived_data_=data_;
					clout.print_debug("Recived header:\t"+recived_data_);
					wait_msg();
				}
				else{
					socket_.close();
					status_=CONNECTION_LOST;
					clout.print_error("Unable send msg. Server hang out unexpectly(in msg body)");
					return;
				}
			}); 
		}
	else{
		socket_.close();
		status_=CONNECTION_LOST;
		clout.print_error("Unable send msg. Server hang out unexpectly(in msg head)");
		return;
	}
	});
	
}


void server_connection::sync_wait_msg(){
	mutex_wait_msg_.wait();
	clout.print_debug(std::string("Waiting msg from server,socket to server is")+ std::to_string(socket_.is_open()));
	boost::asio::async_read(socket_,boost::asio::buffer(header_, HEADER_LENGTH),[this](boost::system::error_code error, std::size_t length){
		if (!error){
			char header[HEADER_LENGTH + 1] = "";
			std::strncat(header, header_, HEADER_LENGTH);
			recived_ = std::atoi(header);
			clout.print_debug(std::string("Recived header:\t")+header_);
			boost::asio::async_read(socket_,boost::asio::buffer(data_, recived_),[this](boost::system::error_code error, std::size_t length){
				if (!error){
					data_[recived_]='\0';
					recived_data_=data_;
					clout.print_debug("Recived data:\t"+recived_data_);
					mutex_msg_recived_.post();
					sync_wait_msg();
				}
				else{
					socket_.close();
					status_=CONNECTION_LOST;
					clout.print_error("Unable send msg. Server hang out unexpectly(in msg body)");
					mutex_msg_recived_.post();;
				}
			}); 
		}
		else{
			socket_.close();
			status_=CONNECTION_LOST;
			clout.print_error("Unable send msg. Server hang out unexpectly(in msg head)");
			mutex_msg_recived_.post();
			return;
			
		}
	});
}


void server_connection::wait_maze_update(client_maze** maze_ptr){
	mutex_wait_msg_.wait();
	clout.print_debug(std::string("Waiting msg from server,socket to server is")+ std::to_string(socket_.is_open()));
	boost::asio::async_read(socket_,boost::asio::buffer(header_, HEADER_LENGTH),[this,maze_ptr](boost::system::error_code error, std::size_t length){
		if (!error){
			char header[HEADER_LENGTH + 1] = "";
			std::strncat(header, header_, HEADER_LENGTH);
			recived_ = std::atoi(header);
			clout.print_debug(std::string("Recived header:\t")+header_);
			boost::asio::async_read(socket_,boost::asio::buffer(data_, recived_),[this,maze_ptr](boost::system::error_code error, std::size_t length){
				if (!error){
					data_[recived_]='\0';
			recived_data_=data_;
			clout.print_debug("Recived data:\t"+recived_data_);
			std::size_t found = recived_data_.find("finish");
			if(found!=std::string::npos){
				clout.print("--==KONEC HRY==--");
				for (unsigned int i = 0; i < (*maze_ptr)->players_.size(); i++){
					if((*maze_ptr)->players_.at(i)->get_state() != 2){
						clout.print("Player number: " + std::to_string(i) + " stay alive!");
						clout.print("Number of steps: " + std::to_string((*maze_ptr)->players_.at(i)->get_steps()));
					}
				}
				return;
			}else if(recived_data_.compare(0,17, "send_game_change ") == 0){
				recived_data_.erase(0,17);
				clout.print_debug("Handle update...");
				clout.print_debug(recived_data_);
				(*maze_ptr)->maze_update(recived_data_);
				clout.print_debug("Update was hadled...");
				(*maze_ptr)->print_maze();
				mutex_wait_msg_.post();
				wait_maze_update(maze_ptr);
				return;
			}
			mutex_msg_recived_.post();
			wait_maze_update(maze_ptr);
				}
				else{
					socket_.close();
					status_=CONNECTION_LOST;
					clout.print_error("Unable send msg. Server hang out unexpectly(in msg body)");
					mutex_msg_recived_.post();;
				}
			}); 
		}
		else{
			socket_.close();
			status_=CONNECTION_LOST;
			clout.print_error("Unable send msg. Server hang out unexpectly(in msg head)");
			mutex_msg_recived_.post();
			return;
			
		}
	});
}


std::string server_connection::sync_msg(){
	mutex_msg_recived_.wait();
	std::string response=recived_data_;
	mutex_wait_msg_.post();
	return response;
}


void server_connection::connect(tcp::resolver::iterator endpoint_iterator){
	boost::asio::connect(socket_, endpoint_iterator);
	clout.print_error("Client is connected to server ...");
}

void server_connection::stop(){
	socket_.close();
	io_->stop();
}

std::string server_connection::parse_arguments(std::string message){
	std::string ret;
	if(message.compare(0,9, "send_maze") == 0){
		message.erase(0,9);
		ret = message;
	}else if(message.compare(0,16, "send_game_change") == 0){
		std::cout << "start" << std::endl;
		unsigned int i = 17;
		std::string active;
		int space = 0;
		// send_game_change OBJ XxY OBJ....
		while(i < message.length()){
			if(isalpha(message[i])){
				// sudej pocet mezer
				if(space % 2 == 0){
					active += message[i];
				}else{	
					clout.print_debug(std::string("sour x: ") + std::string(active));
					active = "";
				}
			}else if(isdigit(message[i])){
				active += message[i];
			}else if(message[i] == ' '){
				// sudej pocet mezer
				if(space % 2 == 0){
					clout.print_debug(std::string("obj : ") + std::string(active));
					active = "";
				}else{
					clout.print_debug(std::string("sour y: ") + std::string(active));
					active = "";
				}
				space++;
				
			}
			i++;
		}
		clout.print_debug(std::string("sour y: ") + std::string(active));
	}else if(message.compare(0,10, "send_lobby") == 0){
		unsigned int i = 11;
		std::string game_name,maze_name,player_count,game_num;
		int comma = 0;
		while(i < message.length()){
			if(message[i] == ' '){
				comma = 0;
				std::cout << game_name << " " << maze_name << " " << player_count << " " << game_num << std::endl;
				game_name = "";
				maze_name = "";
				player_count = "";
				game_num = "";
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
		unsigned int i = 11;
		int comma = 0;
		std::string steps,game_time;
		while(i < message.length()){
			if(message[i] == ' '){
				comma = 0;
				std::cout << steps << " " << game_time << std::endl;
				steps = "";
				game_time = "";
			}else if(message[i] == '-'){
				comma++;
				i++;
			}
		}
	}else{
		// error
	}
	return ret;
}

std::string server_connection::get_lobbys(){
	send_msg("join");
	mutex_msg_recived_.wait();
	std::string data=recived_data_;
	mutex_wait_msg_.post();
	clout.print_debug("Lobbys was returned");
	return data;
}

std::string server_connection::get_mazes(){
	send_msg("create");
	mutex_msg_recived_.wait();
	std::string data=recived_data_;
	mutex_wait_msg_.post();
	clout.print_debug("Mazes was returned");
	return data;
}


std::string server_connection::send_get_lobby(std::string lobby){
	send_msg(lobby);
	mutex_msg_recived_.wait();
	std::string data=recived_data_;
	mutex_wait_msg_.post();
	clout.print_debug("Lobby was returned");
	return data;
}

std::string server_connection::send_create_maze(std::string maze){
	send_msg(maze);
	mutex_msg_recived_.wait();
	std::string data=recived_data_;
	mutex_wait_msg_.post();
	clout.print_debug("Lobby was returned");
	return data;
}


