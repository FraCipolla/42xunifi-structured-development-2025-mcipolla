#include "workout_scheduler.h"

/*
 * You’re building a workout scheduler for a fitness tracking app. The system fetches a
 * user’s data, builds a preliminary workout plan, refines it with the user’s preferences, and
 * then finalizes a complete schedule for a certain number of days. Each day includes personalized
 * exercises and motivational tips.
*/

struct WorkoutPlan *create_workout_schedule(char *username) {
    struct UserData *data = get_user_data(username);
    struct WorkoutPLan *plan = NULL;

    if (data) {
        plan = build_base_plan(data);
        if (plan) {
            struct WorkoutPlan *refine = refine_plan(plan, data);
            if (refine == plan) {
                free(refine);
            } else {
                free(plan);
                plan = refine;
            }
            int duration = determine_duration(plan);
            if (duration > 0) {
                assign_daily_exercises(plan, duration);
                assign_daily_tips(plan, duration);
            } else {
                free_workout_plan(plan);
                plan = NULL;
            }
        }

    }
    free_user_data(data);
    return plan;
}