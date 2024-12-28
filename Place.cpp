#include "Place.h"

Place::Place()
{
	//defualt values
	this->_hasPiece = false;
	this->_location = "";
	this->_pieceName = EMPTY_PLACE;
}

Place::Place(const std::string& location, const char pieceName)
{
	//defualt start as false and loc and piecename
	(pieceName != EMPTY_PLACE) ? this->_hasPiece = true : this->_hasPiece = false;
	this->_location = location;
	this->_pieceName = pieceName;
}

Place::~Place()
{
	
}
void Place::activePiece()
{
	this->_hasPiece = true;
}
void Place::deactivePiece()
{
	this->_hasPiece = false;
}

char Place::getCurrentPiece() const
{
	return this->_pieceName;
}

std::string Place::getLocation() const
{
	return this->_location;
}

void Place::setPiece(const char pieceName)
{
	this->_pieceName = pieceName;
}

bool Place::hasPiece() const
{
	return this->_hasPiece;
}

char Place::getRow() const
{
	return this->_location[COLUM_INDEX];
}
void Place::setLocation(const std::string& location)
{
	this->_location = location;
}
char Place::getLine() const
{
	return this->_location[ROW_INDEX];
}