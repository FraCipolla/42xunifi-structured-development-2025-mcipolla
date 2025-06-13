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
    int core_count = get_available_core_count();
    struct ScheduleResult *result = create_schedule_result(core_count);
    if (result) {
        int current_core = 0;
        while (tasks) {
            struct TaskProfile *profile = profile_tasks(tasks);
            if (profile) {
                struct PriorityMap *priorities = compute_priorities_mock(profile);
                if (priorities) {
                    int task_id = select_best_task_for_current_priorities(profile, priorities);
                    update_schedule_entry(result, current_core, task_id);
                    if (current_core == core_count - 1) {
                        current_core = 0;
                    } else {
                        current_core++;
                    }
                    free_priority_map(priorities);
                }
                free_task_profile(profile);
            }
            // assuming tasks is a list
            tasks = tasks->next;
        }
    }
    return result;
}