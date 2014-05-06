// Project labirinth of doom ICP2014
// Dev team:
////////////////////////////////////
// Seidl Antonin  - xseidl01
// Skyva Petr     - xskyva02
///////////////////////////////////
// load.cpp

#include "load.hpp"
#include "output.hpp"

namespace fs = boost::filesystem;


loader::loader(){

}

void loader::load_all_files(std::string path)
{
	std::string files;

	fs::path full_path(fs::initial_path<fs::path>());
  	full_path = fs::system_complete(fs::path(path));

  	if(!fs::exists(full_path)){
	    out.print_error("Path dont exists");
  	}

  	if(fs::exists(full_path)){
	    fs::directory_iterator end_iter;
	    for(fs::directory_iterator dir_itr(full_path); dir_itr != end_iter; ++dir_itr ){
      		try{
	        	if(fs::is_regular_file(dir_itr->status())){
	        		// files = std::string();
	        		files_.push_back(dir_itr->path().filename().string());
          			// std::cout << dir_itr->path().filename() << "\n";
        		}
      		}catch(const std::exception &ex){
		      	out.print_error(ex.what());
      		}
    	}
  	} 	
}

void loader::print_files(){
	for (unsigned int i = 0; i < files_.size(); i++){
		out.print(files_.at(i));
	}
}

void loader::use_specific(std::string regex){
	std::size_t found; 

	for (unsigned int i = 0; i < files_.size(); i++){
		found = files_.at(i).find(regex);
		if (found!=std::string::npos){
			matched_.push_back(files_.at(i));
		}
	}
}

void loader::print_matched(){
	for (unsigned int i = 0; i < matched_.size(); i++){
		out.print(matched_.at(i));
	}
}


// int main(int argc, char* argv[]){
// 	out.set_debug(true);
// 	loader load;
// 	load.load_all_files("./levels");
// 	load.print_files();
// 	load.use_specific("level");
// 	load.print_matched();
//    	return 0;
// }