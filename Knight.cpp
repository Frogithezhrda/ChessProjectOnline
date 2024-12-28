#include "Knight.h"


Knight::Knight(const char pieceColor, const Place& firstPlace) : Piece(pieceColor, (pieceColor == WHITE ? KnightName : std::toupper(KnightName)), firstPlace)
{

}

Knight::~Knight()
{

}
int Knight::isValidMove(const Place& dest, Board* board, Player* player, Player* opponentPlayer) const
{
    //getting rows and lines
    char currentRow = this->getCurrentPlace().getRow();
    int currentLine = int(this->getCurrentPlace().getLine());
    char destRow = dest.getRow();
    int destLine = int(dest.getLine());
    int code = isBasicValid(dest, board, player); //checking basic valid
    int rowDiff = 0;
    int lineDiff = 0;
    int rowKingDiff = 0;
    int lineKingDiff = 0;
    int rowKingCheckDiff = 0;
    int lineKingCheckDiff = 0;
    //if the code is a not a goodmove than return the error code
    if (code)
    {
        return code;
    }
    //checking  the differences between the king and the dest, with the current and the destm and current and king
    rowKingDiff = abs(destRow - opponentPlayer->getKing()->getCurrentPlace().getRow());
    lineKingDiff = abs(destLine - opponentPlayer->getKing()->getCurrentPlace().getLine());
    rowDiff = abs(currentRow - destRow);
    lineDiff = abs(currentLine - destLine);
    rowKingCheckDiff = abs(currentRow - opponentPlayer->getKing()->getCurrentPlace().getRow());
    lineKingCheckDiff = abs(currentLine - opponentPlayer->getKing()->getCurrentPlace().getLine());
    //checking if moving like a knight
    if (!((rowDiff == ALLOWED_BIG_STEP && lineDiff == ALLOWED_SMALL_STEP) || (rowDiff == ALLOWED_SMALL_STEP && lineDiff == ALLOWED_BIG_STEP)))
    {
        return NotValidMove;
    }
    //checking if the king is between a knight so it will create a check
    if ((rowKingDiff == ALLOWED_BIG_STEP && lineKingDiff == ALLOWED_SMALL_STEP) || (rowKingDiff == ALLOWED_SMALL_STEP && lineKingDiff == ALLOWED_BIG_STEP))
    {
        return CheckMove;
    }
    //checking if we are checking for checks
    if (std::tolower(dest.getCurrentPiece()) == KING)
    {
        //using the king and the current knight to check if he will check the king
        if ((rowKingCheckDiff == ALLOWED_BIG_STEP && lineKingCheckDiff == ALLOWED_SMALL_STEP) || (rowKingCheckDiff == ALLOWED_SMALL_STEP && lineKingCheckDiff == ALLOWED_BIG_STEP))
        {
            opponentPlayer->activateCheck();
            return CheckMove;
        }
    }

    return GoodMove;
}