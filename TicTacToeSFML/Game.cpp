#include "Game.h"
#include <iostream>

#include "AIPlayer.h"

Game::Game(sf::RenderWindow* inWindow) : mWindow(inWindow)
{

	if (!crossTexture.loadFromFile("cross2.png"))
		std::cout << "cross failed to load!";

	if (!circleTexture.loadFromFile("circle2.png"))
		std::cout << "circle failed to load!";

	AI = new AIPlayer(this);
}

Game::~Game()
{
}

void Game::gameLoop()
{

	if (!mWindow) { return; }

	sf::Clock clock;
	float lastFrame = 0;

	//making grid
	sf::Texture gridTexture;
	if (!gridTexture.loadFromFile("grid.png"))
	{
		std::cerr << "failed to load grid" << std::endl;
		exit(1);
	}
	sf::Sprite grid;
	grid.setTexture(gridTexture);
	grid.setScale(10, 10);
	sprites.push_back(&grid);

	sf::Font font;
	if (!font.loadFromFile("sansation.ttf"))
		std::cerr << "failed to load font" << std::endl;
	
	text = new sf::Text();
	text->setFont(font);
	text->setString("");
	text->setCharacterSize(48);
	text->setFillColor(sf::Color::Magenta);
	text->setPosition(STRIDE, STRIDE+STRIDE/3);

	while (mWindow->isOpen())
	{

		sf::Time dt = clock.restart();
		sf::Event event;
		while (mWindow->pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
				mWindow->close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (roundNotOver && circleTurn)
				{
					sf::Vector2i chosenLoc= findPressedSquare(sf::Mouse::getPosition() - mWindow->getPosition());	//will always choose one
					if (checkPositionValidity(chosenLoc))
					{
						placePiece(chosenLoc, 1);
					}
				}
			}
		}

		mWindow->clear(sf::Color(255, 255, 255));
		for (auto& sprite : sprites)
			mWindow->draw(*sprite);
		mWindow->draw(*text);
		mWindow->display();

		if (roundNotOver && !circleTurn)
			AI->makeMove();
	}
}

void Game::makeCircle(sf::Vector2i spawnPos)
{
	sf::Sprite* circle = new sf::Sprite();
	circle->setTexture(circleTexture);
	circle->setScale(10, 10);
	circle->setPosition(spawnPos.x,spawnPos.y);
	sprites.push_back(circle);
}

void Game::makeCross(sf::Vector2i spawnPos)
{
	sf::Sprite* cross = new sf::Sprite();
	cross->setTexture(crossTexture);
	cross->setScale(10, 10);
	cross->setPosition(spawnPos.x, spawnPos.y);
	sprites.push_back(cross);
}

sf::Vector2i Game::findPressedSquare(sf::Vector2i pressedPos)
{
	sf::Vector2i spawnPos;
	if (pressedPos.x < STRIDE-10)
	{
		if (pressedPos.y < STRIDE-10)
			spawnPos = sf::Vector2i(0,0);
		else if (pressedPos.y < 2* STRIDE-10)
			spawnPos = (sf::Vector2i(0, 1));
		else
			spawnPos = (sf::Vector2i(0, 2));
	}
	else if (pressedPos.x < 2*STRIDE-10)
	{
		if (pressedPos.y < STRIDE-10)
			spawnPos = (sf::Vector2i(1, 0));
		else if (pressedPos.y < 2*STRIDE -10)
			spawnPos = (sf::Vector2i(1, 1));
		else
			spawnPos = (sf::Vector2i(1, 2));
	}
	else 
	{
		if (pressedPos.y < STRIDE -10)
			spawnPos = (sf::Vector2i(2, 0));
		else if (pressedPos.y < 2* STRIDE-10)
			spawnPos = (sf::Vector2i(2, 1));
		else
			spawnPos = (sf::Vector2i(2, 2));
	}
	return spawnPos;

}

bool Game::checkPositionValidity(sf::Vector2i pos)
{
	if (mBoard[pos.x][pos.y] == 0)
	{
		text->setString("");
		return true;
	}
	else
	{
		text->setString("invalid position!");
		return false;
	}
}

bool Game::checkWin(int b[3][3])
{
	int intToLookFor = 2; //something that should never be on the board
	circleTurn ? intToLookFor = 1 : intToLookFor = -1;

	int   diagonalResult1 = 0,  diagonalResult2 = 0;
	for (int i = 0; i < 3; i++)
	{
		int columnResult = 0, rowResult = 0;
		for (int j = 0; j < 3; j++)
		{
			if (b[j][i] == intToLookFor)
				rowResult++;
			if (b[i][j] == intToLookFor)
				columnResult++;
		}
		if (b[i][i] == intToLookFor)
			diagonalResult1++;
		if (b[i][2 - i] == intToLookFor)
			diagonalResult2++;
		if (rowResult == 3 || columnResult == 3 || diagonalResult1 == 3 || diagonalResult2 == 3)
		{
			if (intToLookFor == 1)
			{
				text->setString("Circle Won!");
				std::cout << "circle won!";
				return true;
			}
			else
			{
				text->setString("Cross Won!");
				std::cout << "Cross won!";
				return true;
			}
		}
	}
	if (!remainingMovesExists(mBoard))		//TODO: Move this out
	{
		text->setString("Game over!");
		std::cout << "Game Over!";
		return true;
	}
	return false;
}

void Game::placePiece(sf::Vector2i location, int piece)
{
	if (piece == 1)
	{
		makeCircle(location*STRIDE);
		circleTurn = false;
	}
	else if (piece == -1)
	{
		makeCross(location*STRIDE);
		circleTurn = true;
	}
	else
	{
		std::cout << "Wrong piece!";
		return;
	}
	mBoard[location.x][location.y] = piece;
	roundNotOver = !checkWin(mBoard);
}

bool Game::remainingMovesExists(int b[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (b[i][j] == 0)
			{
				return true;
			}
		}
		std::cout <<  std::endl;

	}

	return false;
}

