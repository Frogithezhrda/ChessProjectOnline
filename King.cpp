#include "King.h"
#include "Player.h"
#include "Board.h"


King::King(const char pieceColor, const Place& firstPlace) : Piece(pieceColor, (pieceColor == 'w' ? KingName : std::toupper(KingName)), firstPlace)
{

}
King::~King()
{

}

int King::isValidMove(const Place& dest, Board* board, Player* player, Player* opponentPlayer) const
{
	//king liens and rows
	char currentRow = this->getCurrentPlace().getRow();
	int currentLine = int(this->getCurrentPlace().getLine());
	char pieceColor = islower(dest.getCurrentPiece()) ? WHITE : BLACK; //piece color
	int differenceVertical = currentLine - int(dest.getLine());
	int differenceHorizontal = int(currentRow) - int(dest.getRow());
	Place opponentKingPlace = opponentPlayer->getKing()->getCurrentPlace(); //getting the opp king
	int opponentKingRow = opponentKingPlace.getRow();
	int opponentKingLine = opponentKingPlace.getLine();
	int i = 0;
	int code = isBasicValid(dest, board, player);
	//checking a basic valid move
	if (code)
	{
		return code;
	}
	//checking the valid move if its 1 step 
	if (differenceVertical > STEP || differenceVertical < BACK_STEP || differenceHorizontal > STEP || differenceHorizontal < BACK_STEP)
	{
		return NotValidMove;
	}
	//checking that kings arent close to each other like its disallowed in chess
	if (abs(dest.getRow() - opponentKingRow) <= STEP && abs(dest.getLine() - opponentKingLine) <= STEP)
	{
		return NotValidMove;
	}
	return GoodMove;
}