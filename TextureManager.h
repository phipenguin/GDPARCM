#pragma once
#include "IExecutionEvent.h"
#include "ThreadPool.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <mutex>

class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> TextureTable;

public:
	static TextureManager* getInstance();

	void loadFromAssetList(); //loading of all assets needed for startup
	void loadStreamingAssets();
	void loadSingleStreamAsset(int index, IExecutionEvent* execution_event); //loads a single streaming asset based on index in directory
	sf::Texture* getFromTextureMap(const String asset_name, int frame_index);
	int getNumFrames(const String asset_name);

	sf::Texture* getStreamTextureFromList(int index);
	int getNumLoadedStreamTextures() const;

	int streaming_asset_count = 0;

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* shared_instance;

	TextureTable texture_table;
	TextureList base_texture_list;
	TextureList stream_texture_list;

	//const std::string STREAMING_PATH = "Media/Streaming/";
	const std::string STREAMING_PATH = "Assets/Images/Video/";

	ThreadPool* thread_pool;

	void countStreamingAssets();
	void instantiateAsTexture(String path, String asset_name, bool is_streaming);

	std::mutex guard;

	friend class StreamAssetLoader;
};