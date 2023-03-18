#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Game: sf::NonCopyable
{
public:
	static Game* getInstance();

	void run();
	float getFPS();

	static const sf::Time TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

private:
	Game();
	Game(Game const&) {};             // copy constructor is private
	Game& operator=(Game const&) {};  // assignment operator is private
	static Game* shared_instance;

	sf::RenderWindow main_window;
	float fps = 0.0f;
	int frames = 0;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);

	sf::RectangleShape loading_bar;
	int number_of_threads;
};