#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow* inWindow) : mWindow(inWindow)
{

	if (!crossTexture.loadFromFile("cross2.png"))
	{
		std::cout << "cross failed to load!";
	}

	if (!circleTexture.loadFromFile("circle2.png"))
	{
		std::cout << "circle failed to load!";
	}
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
	{
		std::cerr << "failed to load font" << std::endl;
	}
	text = new sf::Text();
	text->setFont(font);
	text->setString("");
	text->setCharacterSize(48);
	text->setFillColor(sf::Color::Magenta);
	text->setPosition(STRIDE, STRIDE+STRIDE/3);

	while (mWindow->isOpen())
	{

		sf::Time dt = clock.restart();
		//std::cout << "dt:" << dt.asSeconds();		
		sf::Event event;
		while (mWindow->pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
				mWindow->close();
			if (event.type == sf::Event::MouseButtonPressed)
				checkSquarePressed(sf::Mouse::getPosition() - mWindow->getPosition());	//will always choose one
		}
		mWindow->clear(sf::Color(255, 255, 255));
		for (auto& sprite : sprites)
			mWindow->draw(*sprite);
		mWindow->draw(*text);
		mWindow->display();
	}
}

void Game::makeCircle(sf::Vector2f spawnPos)
{
	sf::Sprite* circle = new sf::Sprite();
	circle->setTexture(circleTexture);
	circle->setScale(10, 10);
	circle->setPosition(spawnPos.x,spawnPos.y);
	sprites.push_back(circle);
}

void Game::makeCross(sf::Vector2f spawnPos)
{
	sf::Sprite* cross = new sf::Sprite();
	cross->setTexture(crossTexture);
	cross->setScale(10, 10);
	cross->setPosition(spawnPos.x, spawnPos.y);
	sprites.push_back(cross);
}

void Game::checkSquarePressed(sf::Vector2i pressedPos)
{
	sf::Vector2i spawnPos;
	if (pressedPos.x < STRIDE-10)
	{
		if (pressedPos.y < STRIDE-10)
			spawnPos = sf::Vector2i(0,0);
		else if (pressedPos.y < 2* STRIDE-10)
			spawnPos = (sf::Vector2i(0, STRIDE));
		else
			spawnPos = (sf::Vector2i(0, 2* STRIDE));
	}
	else if (pressedPos.x < 2*STRIDE-10)
	{
		if (pressedPos.y < STRIDE-10)
			spawnPos = (sf::Vector2i(STRIDE, 0));
		else if (pressedPos.y < 2*STRIDE -10)
			spawnPos = (sf::Vector2i(STRIDE, STRIDE));
		else
			spawnPos = (sf::Vector2i(STRIDE, 2* STRIDE));
	}
	else 
	{
		if (pressedPos.y < STRIDE -10)
			spawnPos = (sf::Vector2i(2* STRIDE, 0));
		else if (pressedPos.y < 2* STRIDE-10)
			spawnPos = (sf::Vector2i(2*STRIDE, STRIDE));
		else
			spawnPos = (sf::Vector2i(2* STRIDE, 2* STRIDE));
	}
	if (board[spawnPos.x / STRIDE][spawnPos.y / STRIDE] == 0)
	{
		sf::Vector2f spawnPosf = static_cast<sf::Vector2f>(spawnPos);
		if (circleTurn)
		{
			makeCircle(spawnPosf);
			board[spawnPos.x / STRIDE][spawnPos.y / STRIDE] = 1;
		}
		else
		{
			makeCross(spawnPosf);
			board[spawnPos.x / STRIDE][spawnPos.y / STRIDE] = -1;
		}
		text->setString("");
		checkWin();
		circleTurn = !circleTurn;
	}
	else
	{
		text->setString("invalid position!");
	}
}

bool Game::checkWin()
{
	int intToLookFor = 2; //something that should never be on the board
	circleTurn ? intToLookFor = 1 : intToLookFor = -1;

	int   diagonalResult1 = 0,  diagonalResult2 = 0;
	for (int i = 0; i < 3; i++)
	{
		int columnResult = 0, rowResult = 0;
		for (int j = 0; j < 3; j++)
		{
			if (board[j][i] == intToLookFor)
				rowResult++;
			if (board[i][j] == intToLookFor)
				columnResult++;
		}
		if (board[i][i] == intToLookFor)
			diagonalResult1++;
		if (board[i][2 - i] == intToLookFor)
			diagonalResult2++;
		if (rowResult == 3 || columnResult == 3 || diagonalResult1 == 3 || diagonalResult2 == 3)
		{
			if (circleTurn)
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
	return false;
}
