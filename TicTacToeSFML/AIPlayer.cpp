#include "AIPlayer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

AIPlayer::AIPlayer(Game* inGame) : mGame(inGame)
{

}


AIPlayer::~AIPlayer()
{
}

void AIPlayer::makeMove()
{
	std::cout << "ai starting!";
	sf::Vector2i bestMove = findBestMove(mGame->mBoard);
	//startNodeMinimax();
	std::cout << "ai done!";
	mGame->placePiece(bestMove,player);

}

void AIPlayer::startNodeMinimax()
{
	rootNode = new Node(evaluate(mGame->mBoard), sf::Vector2i(-1,-1), mGame->mBoard);

	makeSubNodes(rootNode, true);
}

void AIPlayer::makeSubNodes(Node* node, bool maxTurn)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (node->boardCopy[i][j] == 0)
			{
				if(maxTurn)
					node->boardCopy[i][j] = player;
				else
					node->boardCopy[i][j] = opponent;

				Node* n = new Node(evaluate(node->boardCopy), sf::Vector2i(i,j), node->boardCopy);
				n->parent = node;
				node->nodes.push_back(n);
				makeSubNodes(n, !maxTurn);
				node->boardCopy[i][j] = 0;
			}
		}
	}
}

sf::Vector2i AIPlayer::findBestNode(Node* startNode)
{
	if (startNode->value = 10)
		return startNode->move;	
	for (auto& n : startNode->nodes)
	{
		if (n->value == 10)
		{
			return n->move;
		}
	}

}

sf::Vector2i AIPlayer::findBestMove(int board[3][3])
{
	int bestVal = -1000;
	sf::Vector2i bestMove;
	bestMove.x = -1;
	bestMove.y = -1;

	// Traverse all cells, evaluate minimax function for 
	// all empty cells. And return the cell with optimal 
	// value. 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Check if cell is empty 
			if (board[i][j] == 0)
			{
				// Make the move 
				board[i][j] = player;

				// compute evaluation function for this 
				// move. 
				int moveVal = minimax(board, 0, false);

				// Undo the move 
				board[i][j] = 0;

				// If the value of the current move is 
				// more than the best value, then update 
				// best/ 
				if (moveVal > bestVal)
				{
					bestMove.x = i;
					bestMove.y = j;
					bestVal = moveVal;
				}
			}
		}
	}

	//printf("The value of the best Move is : %d\n\n",bestVal);

	return bestMove;
}

int AIPlayer::evaluate(int b[3][3])
{
	// Checking for Rows for X or O victory. 
	for (int row = 0; row < 3; row++)
	{
		if (b[row][0] == b[row][1] && b[row][1] == b[row][2])
		{
			if (b[row][0] == -1)
				return +10;
			else if (b[row][0] == 1)
				return -10;
		}
	}

	// Checking for Columns for X or O victory. 
	for (int col = 0; col < 3; col++)
	{
		if (b[0][col] == b[1][col] && b[1][col] == b[2][col])
		{
			if (b[0][col] == -1)
				return +10;
			else if (b[0][col] == 1)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory. 
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
	{
		if (b[0][0] == -1)
			return +10;
		else if (b[0][0] == 1)
			return -10;
	}
	if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
	{
		if (b[0][2] == -1)
			return +10;
		else if (b[0][2] == 1)
			return -10;
	}
	// Else if none of them have won then return 0 
	return 0;
}
// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int AIPlayer::minimax(int board[3][3], int depth, bool isMax)
{
	int score = evaluate(board);

	// If Maximizer has won the game return his/her 
	// evaluated score 
	if (score == 10)
		return score-depth;

	// If Minimizer has won the game return his/her 
	// evaluated score 
	if (score == -10)
		return score+depth;

	// If there are no more moves and no winner then 
	// it is a tie 
	if (mGame->remainingMovesExists(board) == false)
		return 0;

	// If this maximizer's move 
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells 
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty 
				if (board[i][j] == 0)
				{
					// Make the move 
					board[i][j] = player;

					// Call minimax recursively and choose 
					// the maximum value 
					best = std::max(best-depth,
						minimax(board, depth + 1, !isMax));

					// Undo the move 
					board[i][j] = 0;
				}
			}
		}
		return best;
	}

	// If this minimizer's move 
	else
	{
		int best = 1000;

		// Traverse all cells 
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty 
				if (board[i][j] == 0)
				{
					// Make the move 
					board[i][j] = opponent;

					// Call minimax recursively and choose 
					// the minimum value 
					best = std::min(best+depth,
						minimax(board, depth + 1, !isMax));

					// Undo the move 
					board[i][j] = 0;
				}
			}
		}
		return best;
	}
}