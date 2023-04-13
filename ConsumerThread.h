#pragma once
#include "IETThread.h"

class ConsumerThread : public IETThread
{
public:
	ConsumerThread(int id);
	~ConsumerThread();

	int getID();

	void run() override;

	bool is_running;

private:
	int id;
};