#include "StreamSoundLoader.h"
#include "AudioManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"
#include <iostream>

StreamSoundLoader::StreamSoundLoader(String path, IExecutionEvent* execution_event)
{
	this->path = path;
	this->exec_event = execution_event;
}

StreamSoundLoader::~StreamSoundLoader()
{
}

void StreamSoundLoader::onStartTask()
{
	Thread::sleep(5000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String asset_name = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	AudioManager::getInstance()->instantiateAsSound(path, asset_name);

	std::cout << "[AudioManager] Loaded streaming sound: " << asset_name << std::endl;

	this->exec_event->onFinishedExecution();
	delete this;
}