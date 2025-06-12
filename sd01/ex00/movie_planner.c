#include "movie_planner.h"

/*
 * You’re planning a chill movie night with your friends. The goal is to orchestrate the process
 * of collecting your friends’ preferences, searching for matching movies, and building
 * a movie plan for the night.
*/

struct Plan *create_movie_night_plan(void) {
    struct Plan *plan = NULL;
    struct Preferences *prefs = get_user_preferences();
    if (prefs) {
        struct MovieList *list = find_movies(prefs);
        if (list) {
            plan = build_plan(list);
            free(list);
        }
        free(prefs);
    }
    return plan;
}