#pragma once
#include <iostream>
#include <string>

#define EMPTY_PLACE '#'
#define WHITE 'w'
#define BLACK 'b'

#define EMPTY_PLACE '#'
#define ROW_INDEX 1
#define COLUM_INDEX 0

class Place
{
public:
	/*
	name: CONSTRUCTOR
	input: none
	*/
	Place();

	/*
	name: CONSTRUCTOR
	input: a refrense to a string that represents the location on the board
	*/
	Place(const std::string& location, const char pieceName);

	/*
	name: DESTRUCTOR
	*/
	virtual ~Place();

	/*
	name: hasPiece
	input: none
	output: true if there is a piece in that place, false otherwise
	description: this functions tell if there is a piece in the current place
	*/
	bool hasPiece() const;
	
	/*
	name: activepiece
	input: none
	output: none
	description: this functions sets field "hasPiece" to true
	*/
	void activePiece();

	/*
	name: deactivepiece
	input: none
	output: none
	description: this functions sets field "hasPiece" to false
	*/
	void deactivePiece();

	/*
	name: setlocation
	input: a refrence to a string that represents a location
	output: none
	description: this function sets the location if the place
	*/
	void setLocation(const std::string& location);

	/*
	name: getrow
	input: none
	output: a char
	description: this function returns the row of the place
	*/
	char getRow() const;

	/*
	name: getline
	input: none
	output: a char
	description: this function returns the line of the place
	*/
	char getLine() const;

	/*
	name: getLocation 
	input: none
	output: a refrence to a string that represents a location on the board
	description: this functions returns the location of the current place
	*/
	std::string getLocation() const;


	/*
	name: setLocation
	input: new location to set
	output: none
	description: sets a new location for the currentPlace
	*/
	void setPiece(const char pieceName);

	/*
	name: getCurrentPiece
	input: none
	output: a char that represents a piece. (# if there isnt)
	description: this functions returns what piece is in the current place. 
	*/
	char getCurrentPiece() const;


private:
	bool _hasPiece; //is there a piece in the place or not
	std::string _location; //the location of the place 
	char _pieceName; //the name of the piece on the board . (# if there isnt)
};