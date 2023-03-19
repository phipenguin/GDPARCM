#pragma once
#include "Thread.h"
#include "IWorkerAction.h"

class IExecutionEvent;
class StreamSoundLoader : public IWorkerAction
{
private:
	typedef std::string String;

public:
	StreamSoundLoader(String path, IExecutionEvent* execution_event);
	~StreamSoundLoader();

private:
	String path;
	IExecutionEvent* exec_event;

	void onStartTask() override;
};