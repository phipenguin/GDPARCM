#pragma once
#include <iostream>
#include <thread>

/// <summary>
/// Representation of a Java/C# like thread class. The behavior must be inherited by a class that needs to be threaded.
/// By: NeilDG
/// </summary>
class Thread
{
public:
	Thread();
	~Thread();

	void start(); //schedules thread execution
	static void sleep(int ms);
	
protected:
	virtual void run() = 0;
};