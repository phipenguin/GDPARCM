#include "GameObjectManager.h"
#include <cstddef>
#include <iostream>

GameObjectManager* GameObjectManager::shared_instance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
	if (shared_instance == nullptr) shared_instance = new GameObjectManager();

	return shared_instance;
}

void GameObjectManager::processInput(sf::Event event, std::string name)
{
	//for (int i = 0; i < this->game_object_list.size(); i++) {
	//	if (this->game_object_list[i]!= nullptr)
	//		this->game_object_list[i]->processInput(event);
	//}

	for (int i = 0; i < this->game_object_list.size(); i++) {
		if (this->game_object_list[i]!= nullptr)
		{
			if (this->game_object_list[i]->getName() == name)
				this->game_object_list[i]->processInput(event);
		}
	}
}

void GameObjectManager::update(sf::Time delta_time)
{
	for (int i = 0; i < this->game_object_list.size(); i++) {
		if (this->game_object_list[i] != nullptr)
			this->game_object_list[i]->update(delta_time);
	}
}

void GameObjectManager::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < this->game_object_list.size(); i++) {
		if (this->game_object_list[i] != nullptr)
			this->game_object_list[i]->draw(window);
	}
}

AGameObject* GameObjectManager::findObjectByName(AGameObject::String name)
{
	if (game_object_table[name] != nullptr)
	{
		return game_object_table[name];
	}
	else
	{
		std::cout << "AGameObject name not found!" << std::endl;
		return nullptr;
	}
}

GameObjectList GameObjectManager::getGameObjectList()
{
	return game_object_list;
}

int GameObjectManager::getActiveObjectsCount()
{
	return static_cast<int>(game_object_list.size());
}

void GameObjectManager::addObject(AGameObject* game_object)
{
	game_object_table[game_object->getName()] = game_object;
	game_object_list.push_back(game_object);
	
	game_object_table[game_object->getName()]->initialize();
}

void GameObjectManager::deleteObject(AGameObject* game_object)
{
	this->game_object_table.erase(game_object->getName());

	int index = -1;
	for (int i = 0; i < this->game_object_list.size(); i++) {
		if (this->game_object_list[i] == game_object) {
			index = i;
			break;
		}
	}

	if (index != -1) {

		this->game_object_list.erase(this->game_object_list.begin() + index);
		game_object_list.shrink_to_fit();
	}

	delete game_object;
}

void GameObjectManager::deleteObjectByName(AGameObject::String name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != nullptr) {
		this->deleteObject(object);
	}	
}