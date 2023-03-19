#pragma once
#include "AGameObject.h"

class BGObject : public AGameObject
{
public:
	BGObject(String name);

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time delta_time) override;

private:
	const float SPEED_MULTIPLIER = 3000.0f;
	float ticks = 0.0f;
	int index = 0;
	bool can_change_bg = false;
};