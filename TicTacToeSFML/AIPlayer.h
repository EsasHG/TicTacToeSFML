#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
struct Node
{
	Node(int inValue, sf::Vector2i inMove, int inBoard[3][3]) : value(inValue), move(inMove)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				boardCopy[i][j] = inBoard[i][j];
			}
		}
	}
	int value;
	int boardCopy[3][3];
	sf::Vector2i move;
	std::vector<Node*> nodes;
	Node* parent = nullptr;
	
};


class AIPlayer
{
public:
	AIPlayer(class Game * inGame);
	~AIPlayer();
	void makeMove();
	void startNodeMinimax();
	void makeSubNodes(Node* node, bool maxTurn);

	sf::Vector2i findBestNode(Node * startNode);

	sf::Vector2i findBestMove(int board[3][3]);
	int evaluate(int b[3][3]);
	int minimax(int board[3][3], int depth, bool isMax);
	class Game* mGame;
	int player = -1;
	int opponent = 1;
	int mBoardCopy[3][3] = { 0 };
	Node* rootNode;
};

