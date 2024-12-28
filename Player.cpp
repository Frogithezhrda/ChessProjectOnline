#include "Player.h"
#include "Board.h"

Player::Player()
{
	//default Player
	this->_playerColor = ' ';
	this->_king = nullptr;
	this->_isChecked = false;
}

Player::Player(const char color, const Board* board)
{
	//currently Player
    this->_playerColor = color;
    char row = (this->_playerColor == WHITE) ? FIRST_ROW_INDEX : LAST_ROW_INDEX;
    int pawnRow = (this->_playerColor == WHITE) ? SECOND_ROW : SECOND_FROM_LAST_ROW;
    Piece* piece = this->_playerColor == WHITE ? board->getPiece(WHITE_KING_LOCATION) : board->getPiece(BLACK_KING_LOCATION);
    this->_king = (King*)(piece);
	this->_isChecked = false;

}

Player::~Player()
{
}

void Player::activateCheck()
{
    this->_isChecked = true;
}
bool Player::isChecked() const
{
    return this->_isChecked;
}


void Player::deactivateCheck()
{
    this->_isChecked = false;
}
King* Player::getKing() const
{
    return this->_king;
}

char Player::getPlayerColor() const
{
	return this->_playerColor;
}

bool Player::isMate() const
{
    return false;
}

