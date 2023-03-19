#pragma once
#include "IExecutionEvent.h"
#include "ThreadPool.h"
#include <SFML/Audio.hpp>
#include <unordered_map>

class AudioManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::SoundBuffer*> SoundList;
	typedef std::unordered_map<String, SoundList> SoundTable;

public:
	static AudioManager* getInstance();

	void loadSingleStreamAudio(int index, IExecutionEvent* execution_event);
	sf::SoundBuffer* getFromSoundMap(const String asset_name, int frame_index);

	int streaming_asset_count = 0;

private:
	AudioManager();
	AudioManager(AudioManager const&) {};             // copy constructor is private
	AudioManager& operator=(AudioManager const&) {};  // assignment operator is private
	static AudioManager* shared_instance;

	SoundTable sound_table;

	const String STREAMING_PATH = "Assets/Audio/Sounds/";

	ThreadPool* thread_pool;

	void countStreamingAssets();
	void instantiateAsSound(String path, String asset_name);

	friend class StreamSoundLoader;
};