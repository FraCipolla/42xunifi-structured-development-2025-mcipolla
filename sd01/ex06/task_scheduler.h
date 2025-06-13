#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H


struct ScheduleResult *schedule_tasks(struct TaskList *tasks);
struct TaskProfile *profile_tasks(struct TaskList *tasks);
struct PriorityMap *compute_priorities_mock(struct TaskProfile *profile);
int get_available_core_count(void);
int select_best_task_for_current_priorities(struct TaskProfile *profile, struct PriorityMap *priorities);
struct ScheduleResult *create_schedule_result(int core_count);
void update_schedule_entry(struct ScheduleResult *result, int core_id, int task_id);
void free_task_profile(struct TaskProfile *profile);
void free_priority_map(struct PriorityMap *priorities);


#endif