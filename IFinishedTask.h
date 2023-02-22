#pragma once
class IFinishedTask
{
public:
	virtual void onFinished(int thread_id) = 0;
};