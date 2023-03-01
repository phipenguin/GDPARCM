#pragma once
#include "Thread.h"

class IWorkerAction;
class IFinishedTask;
class PoolWorkerThread : public Thread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finished_task);
	~PoolWorkerThread();

	int getThreadID();
	void assignTask(IWorkerAction* action);

private:
	int id = 0;
	IWorkerAction* action;
	IFinishedTask* finished_task;

	void run() override;
};