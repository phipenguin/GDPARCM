#include "Thread.h"

Thread::Thread()
{
}

Thread::~Thread()
{
}

void Thread::start()
{
	std::thread(&Thread::run, this).detach(); //detach thread for independent execution. without this, join() function must be called.
}

void Thread::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}