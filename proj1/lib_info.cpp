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

// Helper function to replace underscores with spaces
std::string replaceUnderscores(const std::string &str) {
    std::string result = str;
    std::replace(result.begin(), result.end(), '_', ' ');
    return result;
}

// Helper function to convert time string (mm:ss) to total seconds
int convertTimeToSeconds(const std::string &time_str) {
    int minutes, seconds;
    sscanf(time_str.c_str(), "%d:%d", &minutes, &seconds);
    return minutes * 60 + seconds;
}

// Helper function to convert seconds to time string (mm:ss)
std::string convertSecondsToString(int time) {
    int minutes = time / 60;
    int seconds = time % 60;
    char buffer[6];
    sprintf(buffer, "%d:%02d", minutes, seconds);
    return std::string(buffer);
}

void process_values(const std::string &line, std::map<std::string, Artist> &library){
	std::stringstream ss(line);
	std::string title, time_str, artist_name, album_name, genre;
	int track;

	ss >> title >> time_str >> artist_name >> album_name >> genre >> track;

	// Replace & reassign underscores with spaces
    title = replaceUnderscores(title);
    artist_name = replaceUnderscores(artist_name);
    album_name = replaceUnderscores(album_name);

	// convert the string of time from the line into an int. 
	int duration = convertTimeToSeconds(time_str);

	// Step 3 -- create the song instance and populate
	// TODO: Sanity check that this works on hydra and tesla servers -- works local on isaac's macbook running gnu and setting -Wextra -std=c++11
	Song song = {title, duration};

	// Step 3 test -- skipping optional checks for now
	//std::cout << song.title << " " << track << " " << convertSecondsToString(song.time) << std::endl;

	// Step 5 -- inserting song into album song list. 
	Artist &artist = library[artist_name];
    artist.name = artist_name;
    Album &album = artist.albums[album_name];
    album.name = album_name;
    album.songs[track] = song;
    album.nsongs++;
    album.time += duration;
    artist.nsongs++;
    artist.time += duration;
}

// create a seperate function that can traverse the library structure that we made and inserted values into
void print_library(const std::map<std::string, Artist> &library) {
    for (const auto &artist_pair : library) {
        const Artist &artist = artist_pair.second;
        std::cout << artist.name << std::endl;
        for (const auto &album_pair : artist.albums) {
            const Album &album = album_pair.second;
            std::cout << "\t" << album.name << std::endl;
        }
    }
}


int main(int argc, char **argv) {
    // Error check command line
    if (argc != 1) {
        std::cerr << "Usage: ./lib_info < file.txt\n";
        return 1;
    }
	
	// create global map variable to store items into
	std::map<std::string, Artist> library;
    std::string line;


    while (std::getline(std::cin, line)) {
    	process_values(line, library);
    }
	
	print_library(library);

    return 0;
}
