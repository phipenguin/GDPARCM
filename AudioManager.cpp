#include "AudioManager.h"
#include "StringUtils.h"
#include "StreamSoundLoader.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <thread>

AudioManager* AudioManager::shared_instance = nullptr;

AudioManager* AudioManager::getInstance()
{
	if (shared_instance == nullptr) 
		shared_instance = new AudioManager();

	return shared_instance;
}

void AudioManager::loadSingleStreamAudio(int index, IExecutionEvent* execution_event)
{
	int fileNum = 0;

	for ( auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			String path = entry.path().generic_string();
			StreamSoundLoader* sound_loader = new StreamSoundLoader(path, execution_event);
			this->thread_pool->scheduleTask(sound_loader);

			break;
		}

		fileNum++;
	}
}

sf::SoundBuffer* AudioManager::getFromSoundMap(const String asset_name, int frame_index)
{
	if (!this->sound_table[asset_name].empty()) {
		return this->sound_table[asset_name][frame_index];
	}
	else {
		std::cout << "[AudioManager] No sound found for " << asset_name << std::endl;
		return NULL;
	}
}

AudioManager::AudioManager()
{
	this->countStreamingAssets();
	this->thread_pool = new ThreadPool("StreamSoundThreadPool", this->streaming_asset_count);
	this->thread_pool->startScheduler();
}

void AudioManager::countStreamingAssets()
{
	this->streaming_asset_count = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streaming_asset_count++;
	}
	std::cout << "[AudioManager] Number of streaming sounds: " << this->streaming_asset_count << std::endl;
}

void AudioManager::instantiateAsSound(String path, String asset_name)
{
	//sf::SoundBuffer* buffer = new sf::SoundBuffer();
	//buffer->loadFromFile(path);
	//this->sound_table[asset_name].push_back(buffer);
}