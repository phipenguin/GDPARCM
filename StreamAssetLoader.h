#pragma once
#include "Thread.h"

class IExecutionEvent;
class StreamAssetLoader : public Thread
{
private:
	typedef std::string String;

public:
	StreamAssetLoader(String path, IExecutionEvent* execution_event);
	~StreamAssetLoader();

private:
	String path;
	IExecutionEvent* exec_event;

	void run() override;
};