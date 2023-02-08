#pragma once
#include "AGameObject.h"

class IconObject : public AGameObject
{
public:
	IconObject(String name, int texture_index);
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time delta_time) override;

private:
	int texture_index = 0;
};