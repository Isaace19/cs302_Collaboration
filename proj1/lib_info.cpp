/*
    Collaborators: Isaac Abella and John Cordwell
    Description: using input stream (not file redirection), parse input data. Remove all underscores and convert to whitespace, and
    turn time values grabbed as strings to integers for counting total album time. Store all data into respective data structures.

    Data structure overview:
    Struct Artist -> Struct Album -> Struct Song ||  A map of Artists contains a map of albums containing a map of songs
    Output program to match gradescript exactly.
*/

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
struct Song
{
    std::string title;
    int time; // could also be a string, if kept int, convert to string
};

struct Album
{
    std::map<int, Song> songs;
    std::string name;
    int time;
    int nsongs; // optional variable, makes counting the total amount of songs in each album easier in output. Could be tracked manually
};

struct Artist
{
    std::map<std::string, Album> albums;
    std::string name;
    int time;
    int nsongs;
    struct Artist
    {
        std::map<std::string, Album> albums;
        std::string name;
        int time;
        int nsongs;
    };

    // Replace underscores with spaces
    std::string replaceUnderscores(const std::string &str)
    {
        std::string result = str;
        // could be a auto for loop or manual for loop
        std::replace(result.begin(), result.end(), '_', ' ');
        return result;
    }

    // Convert time to total seconds
    int convertTimeToSeconds(const std::string &time_str)
    {
        int minutes, seconds;
        sscanf(time_str.c_str(), "%d:%d", &minutes, &seconds);
        return minutes * 60 + seconds;
    }

    // Convert seconds to time string for output in print_library function
    std::string convertSecondsToString(int time)
    {
        int minutes = time / 60;
        int seconds = time % 60;
        char buffer[6];
        // c-style code with sprintf returns deprecate warning on -Wextra flag
        sprintf(buffer, "%d:%02d", minutes, seconds);
        return std::string(buffer);
    }

    void process_values(const std::string &line, std::map<std::string, Artist> &library)
    {
        std::stringstream ss(line);
        std::string title, time_str, artist_name, album_name, genre;
        int track;
        void process_values(const std::string &line, std::map<std::string, Artist> &library)
        {
            std::stringstream ss(line);
            std::string title, time_str, artist_name, album_name, genre;
            int track;

            // grab input from input stream, taking the time as a string and converting with our helper functions
            ss >> title >> time_str >> artist_name >> album_name >> genre >> track;

            // Replace & reassign underscores with spaces
            // Replace & reassign underscores with spaces
            title = replaceUnderscores(title);
            artist_name = replaceUnderscores(artist_name);
            album_name = replaceUnderscores(album_name);

            // convert the string of time from the line into an int.
            int duration = convertTimeToSeconds(time_str);
            // convert the string of time from the line into an int.
            int duration = convertTimeToSeconds(time_str);

            Song song = {title, duration};

            // insert songs into album song list and traverse artists/albums in print_library
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

        // function to traverse library map containing a map of artist->album->song
        void print_library(const std::map<std::string, Artist> &library)
        {
            // change to iterator format
            // traverse through artist struct and output data
            for (std::map<std::string, Artist>::const_iterator art_it = library.begin(); art_it != library.end(); ++art_it)
            {
                const Artist &artist = art_it->second;
                std::cout << art_it->first << ": " << art_it->second.nsongs << ", " << convertSecondsToString(artist.time) << std::endl;

                for (std::map<std::string, Album>::const_iterator alb_it = artist.albums.begin(); alb_it != artist.albums.end(); ++alb_it)
                {
                    // print out the album from artist by traversing the album struct
                    const Album &album = alb_it->second;
                    std::cout << "        " << album.name << ": " << album.songs.size() << ", " << convertSecondsToString(album.time) << std::endl;

                    // now traverse the song struct and print each individual song
                    for (std::map<int, Song>::const_iterator song_it = album.songs.begin(); song_it != album.songs.end(); ++song_it)
                    {
                        const Song &song = song_it->second;
                        std::cout << "                " << song_it->first << ". " << song.title << ": " << convertSecondsToString(song.time) << std::endl;
                    }
                }
            }
        }

        int main(int argc, char **argv)
        {
            // assume no error checking needed according to writeup
            std::ifstream inputFile(argv[1]);
            std::map<std::string, Artist> library;
            std::string line;

            while (std::getline(inputFile, line))
            {
                process_values(line, library);
            }

            inputFile.close(); // irrelevant but valid syntax, would close after main ends.

            print_library(library);

            return 0;
        }