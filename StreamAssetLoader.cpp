#include "StreamAssetLoader.h"
#include "TextureManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"
#include <iostream>

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* execution_event)
{
	this->path = path;
	this->exec_event = execution_event;
}

StreamAssetLoader::~StreamAssetLoader()
{
	//std::cout << "Destroying stream asset loader" << std::endl;
}

void StreamAssetLoader::onStartTask()
{
	//std::cout << "Running stream asset loader" << std::endl;

	//simulate loading of very large file
	Thread::sleep(5000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String asset_name = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, asset_name, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << asset_name << std::endl;

	this->exec_event->onFinishedExecution();
	delete this;
}