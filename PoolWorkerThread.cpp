#include "PoolWorkerThread.h"

#include "IWorkerAction.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finished_task)
{
	this->id = id;
	this->finished_task = finished_task;
}

PoolWorkerThread::~PoolWorkerThread()
{
}

int PoolWorkerThread::getThreadID()
{
	return this->id;
}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
	this->action = action;
}

void PoolWorkerThread::run()
{
	this->action->onStartTask();
}