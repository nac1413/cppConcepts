#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>

#define MAX_TASKS 10



void actual_task();

typedef struct {
	int tasks_id;
	int priority;
	std::function<void()> task;
}priority_;

class comp {
public:
	bool operator()(priority_& a, priority_& b) {
		return a.priority < b.priority;
	}
};

class threadPool
{
private:
	int thread_count;
	std::vector<std::thread> worker_thread;
	std::priority_queue<priority_, std::vector<priority_>,comp> tasks;
	std::mutex mut;
	std::condition_variable cv;
	bool _stop;

public:
	threadPool(int count);
	~threadPool();
	void enqueue_task(priority_& task);
};

threadPool::threadPool(int count) : thread_count(count), _stop(false){
	for (int i = 0; i < thread_count; ++i) {
		worker_thread.emplace_back([this] {
			priority_ curr_task;
			while (true){
				std::unique_lock<std::mutex> lock(mut);
				cv.wait(lock, [this] {
					return (!tasks.empty() || _stop);
				});

				if (tasks.empty() && _stop)
					return;

				curr_task = tasks.top();
				tasks.pop();
				lock.unlock();

				curr_task.task();
			}
		});
	}
}

threadPool::~threadPool(){
	{
		std::unique_lock<std::mutex> lock(mut);
		_stop = true;
	}
	cv.notify_all();

	for (int i = 0; i < thread_count; ++i)
		worker_thread[i].join();
}

void actual_task() {
	std::cout << "Actual tasks performed here" << std::endl;
	std::this_thread::sleep_for(std::chrono::microseconds(1000));
}
void threadPool::enqueue_task(priority_& priorities_task) {
	std::unique_lock<std::mutex> lock(mut);
	this->tasks.emplace(priorities_task);
	cv.notify_one();
	lock.unlock();
}
#endif // !_THREADPOOL_H_
