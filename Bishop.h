#ifndef BISHOP_H
#define BISHOP_H
#pragma once
#include "Piece.h"

#define STEP 1
#define BACK_STEP -1

class Bishop : public Piece
{
public:
	/*
	name: CONSTRUCTOR
	input: the piece color, and a place of ots location
	*/
	Bishop(const char pieceColor, const Place& firstPlace);
	
	/*
	name: DESTRUCTOR
	*/
	virtual ~Bishop();

	/*
	name: isValidMove
	input: a refrence to a place(dest), a pointer to the board, a pointer to a player, and a pointer to the opp player.
	output: a num that represents the validility
	description: this function tells if the move is valid or not and why
	*/
	virtual int isValidMove(const Place& dest, Board* board, Player* player, Player* opponentPlayer) const override;

	/*
	name: isclearpath
	input: a refrence to a string(dest), a refrense to a place(src, and a p
	output: a num that represents the validility
	description: this function tells if the path between src to dest is clear or not
	*/
	bool isClearPath(const Place& dest, const Place& src, const Board* board) const;
	
private:
};
#endif