#include "task_scheduler.h"

#include <stddef.h>
#include <stdlib.h>

/*
 * You are building a simulated task scheduler for a multicore CPU system. The program
 * should:
 * 1. Profile the provided task list to evaluate load and I/O patterns.
 * 2. Compute scheduling priorities for each task.
 * 3. Assign tasks to CPU cores using the computed priorities.
*/

struct ScheduleResult *schedule_tasks(struct TaskList *tasks) {
    struct TaskProfile *profile = profile_tasks(tasks);
    struct ScheduleResult *result = NULL;
    static int last_core;
    
    if (profile) {
        struct PriorityMap *priorities = compute_priorities_mock(profile);
        int core_count = get_available_core_count();
        if (priorities) {
            int task_id = select_best_task_for_current_priorities(profile, priorities);
            result = create_schedule_result(core_count);
            if (result) {
                update_schedule_entry(result, last_core, task_id);
                if (last_core == core_count - 1) {
                    last_core = 0;
                } else {
                    last_core++;
                }
            }
            free_priority_map(priorities);
        }
        free_task_profile(profile);
    }
    return result;
}