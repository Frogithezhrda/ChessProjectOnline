#pragma once
#include "Piece.h"
#include "Board.h"
#include "Player.h"

#define STEP 1
#define BACK_STEP -1
#define BIG_STEP 2
#define BACK_BIG_STEP -2

class Pawn : public Piece
{
public:
	/*
	name: CONSTRUCTOR
	input: the piece color, and a place of ots location
	*/
	Pawn(const char pieceColor, const Place& firstPlace);

	/*
	name: DESTRUCTOR
	*/
	virtual ~Pawn();

	/*
	name: isValidMove
	input: a refrence to a place(dest), a pointer to the board, a pointer to a player, and a pointer to the opp player.
	output: a num that represents the validility
	description: this function tells if the move is valid or not and why
	*/
	virtual int isValidMove(const Place& dest, Board* board, Player* player, Player* opponentPlayer) const override;


private:
};
