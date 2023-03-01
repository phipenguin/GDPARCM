#pragma once
#include "AGameObject.h"

class FPSCounter : public AGameObject
{
public:
	FPSCounter();
	~FPSCounter() override;

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time delta_time) override;
	void draw(sf::RenderWindow* target_window) override;

private:
	sf::Time update_time;
	sf::Text* stats_text;
	int frames_passed = 0;

	void updateFPS(sf::Time elapsed_time);
};