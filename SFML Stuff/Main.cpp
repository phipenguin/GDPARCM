#include "Game.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::err().rdbuf(NULL);

    Game::getInstance()->run();
}