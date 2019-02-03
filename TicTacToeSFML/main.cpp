#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "Game.h"

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	Game g(&window);
	g.gameLoop();
	return 0;
}