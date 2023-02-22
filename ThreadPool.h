#pragma once
#include "Thread.h"
#include <queue>
#include <unordered_map>

class PoolWorkerThread;
class IWorkerAction;
class IFinishedTask
{
public:
	virtual void onFinished(int thread_id) = 0;
};

class ThreadPool : public Thread, public IFinishedTask
{
private:
	typedef std::string String;
	typedef std::queue<PoolWorkerThread*> ThreadList;
	typedef std::unordered_map<int, PoolWorkerThread*> ActiveThreadMap;
	typedef std::queue<IWorkerAction*> ActionList;

public:
	ThreadPool(String name, int num_workers);
	~ThreadPool();

	void startScheduler();
	void stopScheduler();
	void scheduleTask(IWorkerAction* action);

private:
	String name;
	bool is_running = false;
	int num_workers = 0;
	ActiveThreadMap active_threads;
	ThreadList inactive_threads;
	ActionList pending_actions;

	void run() override;
	void onFinished(int thread_id) override;
};