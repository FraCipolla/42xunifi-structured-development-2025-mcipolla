#include "playlist_creator.h"

/*
 * You are building a personalized playlist generator for a music app. The program should:
 * 1. Analyze the user’s mood.
 * 2. Build initial filter settings based on default filters.
 * 3. Refine filters according to mood variations.
 * 4. Assemble a final playlist using mood and filter settings:
 * • Depending on filter characteristics, fetch a popular or niche song.
 * • Combine the chosen song into a mood playlist
*/

struct Playlist *create_playlist(void) {
    struct MoodSettings *mood = analyze_user_mood();
    struct FilterSettings *filter = default_filters();
    struct PlayList *play_list = NULL;

    if (mood && filter) {
        int variations = get_mood_variations(mood);
        while (variations > 0) {
            struct FilterSettings *refined = refine_filters(filter);
            if (refined == filter) {
                free_filter_settings(refined);
                refined = NULL;
            }
            if (!refined) break;
            free_filter_settings(mood);
            mood = refined;
            variations--;
        }
        
        struct SongData * song = NULL;
        if (filters_require_popular_song(filter)) {
            song = fetch_popular_song();
        } else {
            song = fetch_niche_song();
        }
        if (song) {
            play_list = combine_with_mood_playlist(song, mood);
            free_song_data(song); 
        }
    }
    if (mood) free_mood_settings(mood);
    if (filter) free_filter_settings(filter);
    return play_list;
}