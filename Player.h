#pragma once
#include "Piece.h"
#include "King.h"

#define LAST_ROW_INDEX '8'
#define FIRST_ROW_INDEX '1'
#define WHITE_KING_LOCATION "d1"
#define BLACK_KING_LOCATION "d8"


class Player//represents the player
{
public:
	Player();
	/*
	name: CONSTRUCTOR
	input: a char that represents the players color (W/B)
	*/
	Player(const char playerColor, const Board* board);

	/*
	name: DESTRUCTOR
	*/
	virtual ~Player();

	/*
	name: getPlayerColor
	input: none
	output: a char that represenyts the players color (W/B)
	description: this functions returns the players color (W/B)
	*/
	char getPlayerColor() const;

	/*
	name: isChecked
	input: none
	output: true is the player is checked, and false otherwise
	description: this functions tells if the player is checked, or not.
	*/
	bool isChecked() const;
	
	/*
	name: ismate
	input: none
	output: true is the player is mate, and false otherwise
	description: this functions tells if the player is mate, or not.
	*/
	bool isMate() const;

	/*
	name: activatecheck
	input: none
	output: none
	description: this functions labels the player as checkable
	*/
	void activateCheck();
	
	/*
	name: deactivatecheck
	input: none
	output: none
	description: this functions delabels the player as checkable
	*/
	void deactivateCheck();

	/*
	name: getPieces
	input: none
	output: retuns a refrence to a vector that has the players pieces
	description: this functions returns a reference to the players pieces
	*/
	King* getKing() const;

private:
	char _playerColor;//the players color (W/B)
	bool _isChecked;//is he checked or not (true == checked)
	King* _king;//a pointer to DA king (tomking ofc)

};
