
#include "student_code.h"

void finalize_stats(SCHEDULER_STATS* stats) {
    // todo
    stats->average_turnaround_time = (stats->sum_of_turnaround_times / stats->num_processes_completed);
    stats->average_response_time = (stats->sum_of_response_time / stats->num_processes_completed);
}


void mark_process_start(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
    // todo
    //p->entry_time = curr_time;
    stats->num_processes_started++;
    float response = curr_time - p->entry_time;
    stats->sum_of_response_time += response;
    //p->process_state = PROC_RUNNING;

}

void mark_process_run(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
    // todo
    p->process_state = PROC_RUNNING;
    p->time_remaining -= time_slice;
    //p->time_remaining = 0.0f;
    //p->priority++;
}

void mark_process_end(SCHEDULER_STATS* stats, PROCESS* p, float end_time, float time_slice_remaining) {
    // todo

    stats->num_processes_completed++;
    float turnaround = end_time - p->entry_time;
    stats->sum_of_turnaround_times += turnaround;
}

int compare_priority(PROCESS p1, PROCESS p2) {
    return (int)p2.priority - (int)p1.priority;
}

PROCESS* priority_process_selector(PROCESS_LIST* pl) {
    PROCESS *p;
    //p = get_minimum(pl, compare_priority);
    p = pl->processes[0];

    for (int i = 1; i < pl->num_processes; i++) {
	PROCESS* temp = pl->processes[i];

	if (temp->priority < p->priority) {
	    p = temp;
	}
    }
    return p;
}

PROCESS* fifo_process_selector(PROCESS_LIST* pl) {
    PROCESS *p;
    // todo
    p = pl->processes[0]; 

    for (int i = 0; i < pl->num_processes; i++) {
        // Need to cycle through processes and pick shortest
	PROCESS* temp = pl->processes[i];
	float tempEntry = temp->entry_time;
	if (tempEntry < p->entry_time) {
	    p = temp;
	}
    }
    return p;
}

PROCESS* rr_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    // todo
    p = get_next(pl);
    mark_last_used(pl, p); // Unsure if I should do this. 
    return p;
}

PROCESS* sjf_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    p = pl->processes[0];

    // todo
    for (int i = 0; i < pl->num_processes; i++) {
        // Need to cycle through processes and pick shortest
	
	PROCESS* temp = pl->processes[i];
	if (temp->length < p->length) {
	    p = temp;
	}
    }
    return p;
}

PROCESS* lifo_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    // todo
    p = pl->processes[0]; 

    for (int i = 0; i < pl->num_processes; i++) {
        // Need to cycle through processes and pick shortest
	PROCESS* temp = pl->processes[i];
	float tempEntry = temp->entry_time;
	if (tempEntry > p->entry_time) {
	    p = temp;
	}
    }
    return p;
}

PROCESS* stcf_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    p = pl->processes[0];
    float length = p->time_remaining;

    // todo
    for (int i = 0; i < pl->num_processes; i++) {
        // Need to cycle through processes and pick shortest
	PROCESS* temp = pl->processes[i];
	float tempLength = temp->time_remaining;
	if (tempLength < length) {
	    p = temp;
	}
    }
    return p;
}

