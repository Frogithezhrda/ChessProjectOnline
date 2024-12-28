#pragma once
#include <iostream>
#include "Place.h"

enum GameCodes { GoodMove = 0, CheckMove, NotPlayerPiece, AlreadyHasPiece, WillBeCheck, NotValidIndex, NotValidMove, SameDestSrc, CheckMate };
enum Pieces {PawnName = 'p', RookName = 'r', QueenName = 'q', KingName = 'k', KnightName = 'n', BishopName = 'b' };
#define EMPTY_PLACE '#'
#define BLACK 'b'
#define WHITE 'w'
#define KING 'k'

#define BASE_LETTER_ASCII_VALUE 'a'
#define BASE_NUM_ASCII_VALUE '1'

class Board;
class Player;

class Piece//represents a piece on the board
{
public:
	/*
	name: CONSTRUCTOR
	input: the piece color, its type, and a place of ots location
	*/
	Piece(const char pieceColor, const char type, const Place& firstPlace);

	/*
	name: DESTRUCTOR
	*/
	virtual ~Piece();

	/*
	name: move
	input: a refrence to a place 
	output: none
	description: this function moves the piece to the given dest
	*/
	int move(const Place& dest, Board* board, Player* player, Player* opponentPlayer);

	/*
	name: isValidMove
	input: a refrence to a place(dest), a pointer to the board, a pointer to a player, and a pointer to the opp player.
	output: a num that represents the validility
	description: this function tells if the move is valid or not and why
	*/
	virtual int isValidMove(const Place& dest, Board* board, Player* player, Player* opponentPlayer) const = 0;

	/*
	name: isBasicValid
	input: a refrence to place(the destination), a pointer to the board, and a pointer to a player
	output: an error code
	description: this function returns basic error codes
	*/
	int isBasicValid(const Place& dest, Board* board, Player* player) const;

	/*
	name: getPieceColor
	input: none
	output:a char that represents the clor of the piece (B/W)
	description: this function returns the color of the piece
	*/
	char getPieceColor() const;

	/*
	name: getCurrentPlace
	input: none
	output:a place
	description: this function returns the place of the piece
	*/
	Place getCurrentPlace() const;

	/*
	name: getType
	input: none
	output: a string that represents a type
	description: this fyunction returns the type of the piece
	*/
	char getType() const;

	/*
	name: setCurrentPlace
	input: the new location
	output: none
	description: this fyunction returns the type of the piece
	*/
	void setCurrentPlace(const Place& dest);

private:
	char _pieceColor;//the color of the piece
	char _type;//the type of piece
	Place _currentPlace;//the current location of the piece
};