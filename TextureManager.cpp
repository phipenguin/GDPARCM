#include "TextureManager.h"
#include "StringUtils.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <thread>
//#include "IETThread.h"

TextureManager* TextureManager::shared_instance = nullptr;

TextureManager* TextureManager::getInstance()
{
	if (shared_instance == nullptr) 
		shared_instance = new TextureManager();

	return shared_instance;
}

void TextureManager::loadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String path;

	while (std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

void TextureManager::loadSingleStreamAsset(int index)
{
	int fileNum = 0;

	for ( auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			//simulate loading of very large file
			//<code here for thread sleeping. Fill this up only when instructor told so.>

			this->instantiateAsTexture(entry.path().string(), entry.path().string(), true);

			//<code here for loading asset>
			//String assetName = "";

			std::cout << "[TextureManager] Loaded streaming texture: " << entry.path().string() << std::endl;
			break;
		}

		fileNum++;
		///std::cout << fileNum << std::endl;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String asset_name, int frame_index)
{
	if (!this->texture_table[asset_name].empty()) {
		return this->texture_table[asset_name][frame_index];
	}
	else {
		std::cout << "[TextureManager] No texture found for " << asset_name << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const String asset_name)
{
	if (!this->texture_table[asset_name].empty()) {
		return this->texture_table[asset_name].size();
	}
	else {
		std::cout << "[TextureManager] No texture found for " << asset_name << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getStreamTextureFromList(int index)
{
	return this->stream_texture_list[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return this->stream_texture_list.size();
}

TextureManager::TextureManager()
{
	this->countStreamingAssets();
}

void TextureManager::countStreamingAssets()
{
	this->streaming_asset_count = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streaming_asset_count++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << this->streaming_asset_count << std::endl;
}

void TextureManager::instantiateAsTexture(String path, String asset_name, bool is_streaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->texture_table[asset_name].push_back(texture);

	if (is_streaming)
	{
		this->stream_texture_list.push_back(texture);
	}
	else
	{
		this->base_texture_list.push_back(texture);
	}
}