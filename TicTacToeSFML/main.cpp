#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

int main()
{

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	Game g(&window);
	g.gameLoop();
	return 0;
}