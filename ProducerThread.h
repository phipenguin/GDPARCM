#pragma once
#include "IETThread.h"

class ProducerThread : public IETThread
{
public:
	ProducerThread();
	~ProducerThread();

	void run() override;

	bool is_running;
};