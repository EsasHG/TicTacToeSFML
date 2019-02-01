#pragma once

#include <SFML/Graphics.hpp>
#define STRIDE 340

class Game
{
public:
	Game(sf::RenderWindow* inWindow);
	~Game();

	void gameLoop();
	void makeCircle(sf::Vector2f spawnPos);
	void makeCross(sf::Vector2f spawnPos);
	void checkSquarePressed(sf::Vector2i pressedPos);
	bool checkWin();
private:
	sf::RenderWindow* mWindow;
	int board[3][3] = { 0 };
	bool circleTurn = true;
	std::vector<class sf::Sprite*> sprites;
	sf::Text* text;
	sf::Texture crossTexture;
	sf::Texture circleTexture;
};

