/*
	Collaborators: Isaac Abella and John Cordwell
	Description: grab a .txt file of unparsed data, and than format
	text and calculate the time of albums.
*/


#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstdio>

// include the struct of Song, Album, and Artist

// music.txt is in a very specific format, each line of stdinput contains six words that
// describes a song in the MP3 library.
// Parse: Title, Time(m:ss), Artist, Album, Genre, Track

struct Song {
	std::string title;
	int time; // could also be a string
};

struct Album {
	std::map <int, Song > songs;
	std::string name;
	int time;
	int nsongs; // optional variable, count number of songs in album
};

struct Artist {
	std::map <std::string, Album > albums;
	std::string name;
		int time;
		int nsongs;
};

// have to convert the time string to mm:ss in total seconds
int convert_timestr(const std::string& string_time){
	int minutes, seconds;
	sscanf(string_time.c_str(), "%d:%d", &minutes, &seconds);
	return minutes * 60 + seconds;
}

// than take total seconds and format into mm:ss
std::string convert_seconds(int time){
	int minutes = time / 60;
	int seconds = time % 60;
	char buffer[6];
	sprintf(buffer, "%d:%02d", minutes, seconds);
	return std::string(buffer);
}

void process_values(const std::string &line, std::map<std::string, Artist*>& artists){

}

void manage_library(const std::map<std::string, Artist*>& artists) {
	
}

int main(int argc, char **argv){
	// error check command line
	if(argc != 2){
		std::cerr << "Usage: ./lib_info < [file.txt]\n";
		return 1;
	}	
	
	

	std::string line;			
	while(getline(std::cin, line)){}
	
	return 0;
}
