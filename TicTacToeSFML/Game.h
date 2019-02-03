#pragma once

#include <SFML/Graphics.hpp>
#define STRIDE 340

class Game
{
public:
	Game(sf::RenderWindow* inWindow);
	~Game();

	void gameLoop();
	void makeCircle(sf::Vector2i spawnPos);

	void makeCross(sf::Vector2i spawnPos);
	sf::Vector2i findPressedSquare(sf::Vector2i pressedPos);
	bool checkPositionValidity(sf::Vector2i pos);
	bool checkWin(int b[3][3]);
	void placePiece(sf::Vector2i location, int piece);
	bool remainingMovesExists(int b[3][3]);
	int mBoard[3][3] = { 0 };
private:
	sf::RenderWindow* mWindow;
	bool circleTurn = true;
	bool roundNotOver = true;
	std::vector<class sf::Sprite*> sprites;
	sf::Text* text;
	sf::Texture crossTexture;
	sf::Texture circleTexture;
	class AIPlayer* AI;

};

