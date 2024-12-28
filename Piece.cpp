#include "Piece.h"
#include "Player.h"
#include "Board.h"

Piece::Piece(const char pieceColor, const char type, const Place& firstPlace)
{
	//stearting piece colors and type
	this->_pieceColor = pieceColor;
	this->_type = type;
	this->_currentPlace = firstPlace;
}

Piece::~Piece()
{
}

Place Piece::getCurrentPlace() const
{
	return this->_currentPlace;
}


char Piece::getPieceColor() const
{
	return this->_pieceColor;
}

char Piece::getType() const
{
	return this->_type;
}

void Piece::setCurrentPlace(const Place& dest)
{
	this->_currentPlace.setLocation(dest.getLocation());
	this->_currentPlace.activePiece();
}

int Piece::move(const Place& dest, Board* board, Player* player, Player* opponentPlayer)
{
	int moveCode = isValidMove(dest, board, player, opponentPlayer);
	if (moveCode == CheckMove || moveCode == GoodMove)//if the move is valid...
	{
		
		if (std::tolower(dest.getCurrentPiece()) != KING)//if cant eat the king
		{
			this->setCurrentPlace(dest);
			//moving the players king
			if (std::tolower(this->_type) == KING && this->getPieceColor() == player->getPlayerColor())
			{
				player->getKing()->setCurrentPlace(dest);
			}
		}
		else
		{
			moveCode = NotValidMove;
		}
	}
	return moveCode;
}

int Piece::isBasicValid(const Place& dest, Board* board, Player* player) const
{
	char destPieceColor = islower(dest.getCurrentPiece()) ? WHITE : BLACK;
	//checking if this is a valid position
	if (!board->isValidPosition(dest.getLocation()))
	{
		return NotValidIndex;
	}
	//checking if they are on the same dest and src
	if (dest.getLocation() == this->getCurrentPlace().getLocation())
	{
		return SameDestSrc; 
	}
	//checking that he actually takes a piece:)
	if (this->getCurrentPlace().getCurrentPiece() == EMPTY_PLACE && dest.getCurrentPiece() != KING)
	{
		return NotPlayerPiece;
	}
	//checking that he doesnt try and eat the same piece color
	if (dest.hasPiece() && destPieceColor == this->getPieceColor())
	{
		return AlreadyHasPiece;
	}
	return GoodMove;
}