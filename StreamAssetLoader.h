#pragma once
#include "Thread.h"
#include "IWorkerAction.h"
#include <mutex>

class IExecutionEvent;
class StreamAssetLoader : public IWorkerAction
{
private:
	typedef std::string String;

public:
	StreamAssetLoader(String path, IExecutionEvent* execution_event);
	~StreamAssetLoader();

private:
	String path;
	IExecutionEvent* exec_event;

	void onStartTask() override;

	std::mutex guard;
};