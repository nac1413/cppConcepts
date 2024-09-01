#include "threadPool.h"

int main() {
	threadPool tp(4);
	priority_ pt[MAX_TASKS];
	for (int i = 0; i < MAX_TASKS; ++i) {
		pt[i].tasks_id = i + 1;
		pt[i].priority = rand() % (MAX_TASKS + 1);
		pt[i].task = actual_task;
		tp.enqueue_task(pt[i]);
	}

	return 0;
}