#pragma once
#include "IETThread.h"

class ConsumerThread : public IETThread
{
public:
	ConsumerThread();
	~ConsumerThread();

	void run() override;

	bool is_running;
};