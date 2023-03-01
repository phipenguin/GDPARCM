#include "ThreadPool.h"
#include "PoolWorkerThread.h"
#include <iostream>

ThreadPool::ThreadPool(String name, int num_workers)
{
	this->name = name;
	this->num_workers = num_workers;

	for (int i = 0; i < this->num_workers; i++)
	{
		this->inactive_threads.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
	this->stopScheduler();
	this->active_threads.clear();
	while (this->inactive_threads.empty() == false)
	{
		this->inactive_threads.pop();
	}
}

void ThreadPool::startScheduler()
{
	this->is_running = true;
	this->start();
}

void ThreadPool::stopScheduler()
{
	this->is_running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pending_actions.push(action);
}

void ThreadPool::run()
{
	while (this->is_running)
	{
		if (this->pending_actions.empty() == false)
		{
			if (this->inactive_threads.empty() == false)
			{
				PoolWorkerThread* worker_thread = this->inactive_threads.front();
				this->inactive_threads.pop();
				this->active_threads[worker_thread->getThreadID()] = worker_thread;

				worker_thread->assignTask(this->pending_actions.front());
				worker_thread->start();
				this->pending_actions.pop();
			}

			else
			{
				//std::cout << "[ThreadPool " << this->name << "] No more available worker threads. Available threads: " << this->inactive_threads.size() << std::endl;
			}
		}

		else
		{
			//std::cout << "[ThreadPool " << this->name << "] No actions scheduled." << std::endl;
		}
	}
}

void ThreadPool::onFinished(int thread_id)
{
	if (this->active_threads[thread_id] != nullptr)
	{
		delete this->active_threads[thread_id];
		this->active_threads.erase(thread_id);

		this->inactive_threads.push(new PoolWorkerThread(thread_id, this));
	}
}