#pragma once
#include <iostream>
#include <string>
#include "Place.h"
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"

#define LAST_ROW_INDEX '8'
#define FIRST_ROW_INDEX '1'
#define LAST_COLUM_INDEX 'h'
#define FIRST_COLUM_INDEX 'a'

#define ROW_INDEX 1
#define COLUM_INDEX 0

#define BLACK 'b'
#define WHITE 'w'
#define BOARD_SIZE 8
#define A_ASCII_VALUE 97

#define SECOND_ROW '2'
#define SECOND_FROM_LAST_ROW '7'

class Board//represents the gameboard
{
public:
	/*
	name: CONSTRUCTOR
	input: none
	*/
	Board(const std::string& initBoard);

	/*
	name: DESTRUCTOR
	*/
	virtual ~Board();
	
	/*
	name: printBoard
	input: none
	output: none
	description: this function print the gameboard :)
	*/
	void printBoard() const;

	/*
	name: setboard
	input: a refrence to a string,(src). and a refrence to a string(dest)
	output: none
	description: this function sets the board by given locations, (moves whats at src to dest)
	*/
	void setBoard(const std::string& src, const Place& dest);

	/*
	name: setpieceatboard
	input: a refrence to a string,(dest). and a pointer to a piece
	output: none
	description: this function inits a piece at given location at the board
	*/
	void setPieceAtBoard(const std::string& dest, Piece* piece);

	/*
	name: getPiece
	input: a refrence to a string
	output: a pinter to apiiece
	description: this function returns a pointer to the piece that is in the given location
	*/
	Piece* getPiece(const std::string& pieceLocation) const;

	/*
	name: getBoard
	input: none
	output: the board
	description: this function returns the board (?)
	*/
	Place* getBoard() const;
	
	/*
	name: isValidPoisitio
	input: a refrense to a string
	output: the board
	description: this function tells if the position is valid
	*/
	bool isValidPosition(const std::string& position) const;

private:
	Place* _board[BOARD_SIZE]; //the board(?)
};