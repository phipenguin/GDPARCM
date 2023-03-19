#pragma once
#include "AGameObject.h"

class P5IconObject : public AGameObject
{
public:
	P5IconObject(String name);

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time delta_time) override;

private:
	float ticks = 0.0f;
	int index = 0;
	bool can_change_icon = false;
};