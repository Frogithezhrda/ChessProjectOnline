#pragma once
#include "Socket.h"
#include "Player.h"
#include "Board.h"
#include "Pipe.h"

#define WHITE_PLAYER 0
#define BLACK_PLAYER 1
#define PLAYER_COUNT 2
#define DELAY 5000
#define TRY_AGAIN "0"
#define INIT_STRING "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"//the board

#define ROW_INDEX 1
#define COLUM_INDEX 0
#define EMPTY_PLACE '#'

#define QUIT "quit"

#define DEST_INDEX 0
#define SRC_INDEX 2

#define NUM_OF_CHARS_IN_LOCATION 2

#define BUFFER 1024
#define PORT "8000"

#define SRC_ROW_INDEX 0
#define DEST_ROW 2
#define SRC_LINE 3
#define DEST_LINE 1
#define LENGTH 4

#define BASE_LETTER_ASCII_VALUE 'a'

enum GameState {Normal='n', StaleMate='s', Mate='w' };
//enum PieceTypes {Pawn='p', Rook='r', Knight='n', Bishop='b', King='k', Queen='q'};


class Manager
{
public:



	/*
	name: CONSTRUCTOR
	input: none
	*/
	Manager(const std::string& initBoard);

	/*
	name: DESTRUCTOR
	*/
	virtual ~Manager();

	/*
	name: handleConsoleMode
	input: none
	output:none
	description: this is handling the console gamemode basic console moves etc..
	*/
	void handleConsoleMode();

	/*
	name: handleConsole
	input: move to handle
	output:none
	description: this function is habdeling the function (console loop)
	*/
	void handleConsole(const std::string& move);

	/*
	name: printTurn
	input: a bool that tells if it whites turn
	output: none
	description: this function prints whos turn it is 
	*/
	void printTurn() const;

	/*
	name: getBoard
	input: none
	output: a refrence to the current board
	description: returns a refrennce to  current board
	*/
	Board& getBoard() const;


	/*
	name: getCurrentPlayer
	input: a bool that represents whos turn it is
	output: a pointer to a player
	description: this function returuns a pointer to the current player
	*/
	Player* getCurrentPlayer();

	/*
	name: getOpponentPlayer
	input: a bool that represents whos turn it is
	output: a pointer to the opp player
	description: this function returuns a pointer to the opp player
	*/
	Player* getOpponentPlayer();

	/*
	name: getWhitePlayer
	input: none
	output: a player
	description: this function resturns the white player
	*/
	Player getWhitePlayer() const;

	/*
	name: getBlackPlayer
	input: none
	output: a player
	description: this function resturns the black player
	*/
	Player getBlackPlayer() const;

	/*
	name: isStillChecked
	input: na bool that represents if its whites move
	output: a player
	description: this function resturns if a player is  checked
	*/
	bool isStillChecked();

	/*
	name: manageMove
	input: a refrence to a string (src), a refrence to a string (dest), and a bool that tells whos turn it is
	output: a player
	description: this function resturns if a player is  checked
	*/
	int manageMove(const std::string& src, const std::string& dest);

	/*
	name: isvalidinput
	input: a refrence to a string that represents a move
	output: a bool
	description: this function tells if the given input is valid or not
	*/
	bool isValidMoveInput(const std::string& move);

	/*
	name: isDiscoveredAttack
	input: src, dest
	output: if the attack was a discovered attack or not
	description: if the move resulted in a discovered attack than it will return true
	*/
	bool isDiscoveredAttack(const std::string& src, const std::string& dest);

	/*
	name: getErrorCode
	input: none
	output: error code
	description: returns the code of the game result
	*/
	int getErrorCode() const;

	/*
	name: handleGraphicsMode
	input: Pipe
	output: none
	description: this is handling the graphics gamemode basic graphics moves etc..
	*/
	void handleGraphicsMode(Pipe& pipe);

	/*
	name: handleMulti
	input: none
	output: none
	description: handling the multiplayer game mode
	*/
	void handleMulti();


private:
	/*
	name: initPieces
	input: player to intialize pieces for
	output: none
	description: initializes pieces on the board for the players
	*/
	void displayError(const int errorCode);


	GameState _gameState; //d = draw, w = win, n = normal
	Player _players[PLAYER_COUNT];
	Board* _board;
	int _errorCode;
	bool _isWhiteTurn;
};