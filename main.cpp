#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <arena.h>
#include <position.h>

int main( int argc, char* argv[] ){
	std::ifstream infile;
	infile.open(argv[1]);
	std::string line;
	
	Arena * arena;
	int height, width, initial_size, initial_show_size;
	int i;
	int initial_i, initial_j, end_i, end_j;

	if (infile.is_open()){
		while (std::getline(infile, line))
		{
		    std::stringstream iss(line);
		    if (i == 0){
		    	iss >> height >> width;
		    }
		    if (i == 1){
		    	iss >> initial_size;
		    }
		    if (i == 2){
		    	iss >> initial_show_size;
		    	arena = new Arena(height, width, initial_size, initial_show_size);
		    }
		    if (i > 2){
		    	for(int j = 0; j< line.length(); j++){
		    		if (line[j] == '@'){
		    			arena->addPosition(new Position(j, i-2));
		    			initial_i = i-2;
		    			initial_j = j;
		    		}
		    		if (line[j] == '1')
		    			arena->addPosition(new Position(j, i-2));
		    		if (line[j] == 'X'){
		    			arena->addPosition(new Position(j, i-2));
		    			end_i = i-2;
		    			end_j = j;
		    		}
		    	}
		    }
		    i++;
		}
		arena->orderPath(initial_i, initial_j, end_i, end_j);
	}
}