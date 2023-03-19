#pragma once
#include "AGameObject.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>

typedef std::unordered_map<std::string, AGameObject*> GameObjectTable;
typedef std::vector<AGameObject*> GameObjectList;

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();

	void processInput(sf::Event event, std::string name);
	void update(sf::Time delta_time);
	void draw(sf::RenderWindow* window);

	AGameObject* findObjectByName(AGameObject::String name);
	GameObjectList getGameObjectList();

	int getActiveObjectsCount();

	void addObject(AGameObject* game_object);
	void deleteObject(AGameObject* game_object);
	void deleteObjectByName(AGameObject::String name);

private:
	GameObjectManager() {};
	GameObjectManager(GameObjectManager const&) {};             // copy constructor is private
	GameObjectManager& operator=(GameObjectManager const&) {};  // assignment operator is private
	static GameObjectManager* shared_instance;

	GameObjectTable game_object_table;
	GameObjectList game_object_list;

};