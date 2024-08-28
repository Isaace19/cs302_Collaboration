// create a seperate function that can traverse the library structure that we made and inserted values into
void print_library(const std::map<std::string, Artist> &library)
{
    // First iterator acesses the library of artists
    for (std::map<std::string, Artist>::const_iterator art_it = library.begin(); art_it != library.end(); ++art_it)
    {
        const Artist &artist = art_it->second;
        std::cout << artist.name << ": " << artist.nsongs << ", " << convertSecondsToString(artist.time) << std::endl;

        // Now accesses the map of each album of the current artist
        for (std::map<std::string, Album>::const_iterator alb_it = artist.albums.begin(); alb_it != artist.albums.end(); ++alb_it)
        {
            // print out the
            const Album &album = alb_it->second;
            std::cout << "        " << album.name << ": " << album.songs.size() << ", " << convertSecondsToString(album.time) << std::endl;

            // Now output the songs in each album
            for (std::map<int, Song>::const_iterator song_it = album.songs.begin(); song_it != album.songs.end(); ++song_it)
            {
                // tweak this printing for 16 spaces according to vimdiff
                const Song &song = song_it->second;
                std::cout << "                " << song_it->first << ". " << song.title << ": " << convertSecondsToString(song.time) << std::endl;
            }
        }
    }
}