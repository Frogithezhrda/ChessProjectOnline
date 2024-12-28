#include "Queen.h"

Queen::Queen(const char pieceColor, const Place& firstPlace) : Piece(pieceColor, (pieceColor == WHITE ? QueenName : std::toupper(QueenName)), firstPlace)
{

}

Queen::~Queen() {}

int Queen::isValidMove(const Place& dest, Board* board, Player* player, Player* opponentPlayer) const
{
	//we create a rock and bishop in the current place
	Rook rook = Rook(this->getPieceColor(), this->getCurrentPlace());
	Bishop bishop = Bishop(this->getPieceColor(), this->getCurrentPlace());
	int rookCode = rook.isValidMove(dest, board, player, opponentPlayer); //getting the moves codes
	int bishopCode = bishop.isValidMove(dest, board, player, opponentPlayer);
	//getting the king and rook and bishop for checking if it will be check
	Place opponentKingPlace = opponentPlayer->getKing()->getCurrentPlace();
	Rook rookCheck = Rook(this->getPieceColor(), dest);
	Bishop bishopCheck = Bishop(this->getPieceColor(), dest);
	//checking if they create a check
	if (bishopCode == CheckMove || rookCode == CheckMove)
	{
		return CheckMove;
	}
	//if its a good move
	if (rookCode == GoodMove || bishopCode == GoodMove)
	{
		//than check for a check
		if (rookCheck.isValidMove(opponentKingPlace, board, player, opponentPlayer) == CheckMove ||
			bishopCheck.isValidMove(opponentKingPlace, board, player, opponentPlayer) == CheckMove)
		{
			return CheckMove;
		}
		return GoodMove;
	}
	//return the code
	return rookCode;
}
