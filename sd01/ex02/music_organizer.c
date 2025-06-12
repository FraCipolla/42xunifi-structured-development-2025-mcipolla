#include "music_organizer.h"

#include <stddef.h>
#include <stdlib.h>

/*
 * You’re a music enthusiast and want to organize your vast digital music library. Your goal
 * is to automate the process of scanning music files, categorizing them, and updating a
 * central music database.
*/

struct MusicLibrary *organize_music_library(const char *directory_path) {
    struct MusicLibrary *music_lib = create_music_library();
    
    if (directory_path) {
        const char **music_files = scan_directory(directory_path);
        
        if (music_files && music_lib) {
            while (*music_files) {
                struct MusicFile *file = process_music_file(directory_path, *music_files);
                update_music_library(music_lib, file);
                ++music_files;
            }
        }
    }

    return music_lib;
}