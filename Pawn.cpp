#include "Pawn.h"

Pawn::Pawn(const char pieceColor, const Place& firstPlace) : Piece(pieceColor, (pieceColor == 'w' ? PawnName : std::toupper(PawnName)), firstPlace)
{
}


Pawn::~Pawn()
{

}
int Pawn::isValidMove(const Place& dest, Board* board, Player* player, Player* opponentPlayer) const
{
    //starting rows and lines
    char currentRow = this->getCurrentPlace().getRow();
    char currentLine = this->getCurrentPlace().getLine();
    int differenceVertical = currentLine - int(dest.getLine());
    int differenceHorizontal = int(currentRow) - int(dest.getRow());
    char kingRow = opponentPlayer->getKing()->getCurrentPlace().getRow();
    char kingLine = opponentPlayer->getKing()->getCurrentPlace().getLine();
    int code = isBasicValid(dest, board, player);
    //middle postions for the 2 jumps
    std::string middlePosition = "";
    char middleRow = ' ';
    Piece* middlePiece = nullptr;

    if (code)
    {
        return code;
    }

    //checking if you can eat and that you dont eat your own piece
    if (differenceHorizontal == STEP || differenceHorizontal == BACK_STEP)
    {
        if ((this->getPieceColor() == WHITE && differenceVertical == BACK_STEP) ||
            (this->getPieceColor() == BLACK && differenceVertical == STEP))
        {
            if (dest.hasPiece())
            {
                //checking if you will check
                if ((std::abs(int(dest.getRow()) - int(kingRow)) == STEP) && (std::abs(int(dest.getLine()) - int(kingLine)) == STEP))
                {
                    return CheckMove;
                }
                //checking if the checks for checks will check if he will create check
                else if ((std::abs(int(this->getCurrentPlace().getRow()) - int(kingRow)) == STEP) && (std::abs(int(this->getCurrentPlace().getLine()) - int(kingLine)) == STEP))
                {
                    return CheckMove;
                }
                return GoodMove; 
            }
        }
        return NotValidMove; 
    }
    //checking for moving forward
    if (differenceHorizontal == 0 && ((this->getPieceColor() == WHITE && differenceVertical == BACK_STEP) ||
        (this->getPieceColor() == BLACK && differenceVertical == STEP)))
    {
        if (!dest.hasPiece()) 
        {
            //checking if the next move will creat check
            if ((std::abs(int(dest.getRow()) - int(kingRow)) == STEP) && (std::abs(int(dest.getLine()) - int(kingLine)) == STEP))
            {
                return CheckMove;
            }
            //checking if the checks for checks will check if he will create check
            else if ((std::abs(int(this->getCurrentPlace().getRow()) - int(kingRow)) == STEP) && (std::abs(int(this->getCurrentPlace().getLine()) - int(kingLine)) == STEP))
            {
                return CheckMove;
            }
            return GoodMove;
        }
    }
    //if there is a piece its not a valid move
    if (dest.hasPiece())
    {
        return NotValidMove;
    }
    //checking for a 2 jump only from the start
    if ((this->getPieceColor() == WHITE && this->getCurrentPlace().getLine() == SECOND_ROW) ||
        (this->getPieceColor() == BLACK && this->getCurrentPlace().getLine() == SECOND_FROM_LAST_ROW))
    {
        //checking if its a two jump
        if (((this->getPieceColor() == WHITE && differenceVertical == BACK_BIG_STEP) ||
            (this->getPieceColor() == BLACK && differenceVertical == BIG_STEP)) && differenceHorizontal == 0)
        {
            //if there is a piece in the middle than you cant jump
            middleRow = currentLine + (differenceVertical / BIG_STEP) * -1;
            middlePosition = std::string(1, currentRow) + middleRow;
            middlePiece = board->getPiece(middlePosition);
            if (middlePiece != nullptr)
            {
                //cleaning piece
                delete middlePiece;
                return NotValidMove;
            }
            //checking if the move will create a check
            if ((std::abs(int(dest.getRow()) - int(kingRow)) == 1) && (std::abs(int(dest.getLine()) - int(kingLine)) == 1))
            {
                return CheckMove;
            }
            //checking if the checks for checks will check if he will create check
            else if ((std::abs(int(this->getCurrentPlace().getRow()) - int(kingRow)) == 1) && (std::abs(int(this->getCurrentPlace().getLine()) - int(kingLine)) == 1))
            {
                return CheckMove;
            }
            return GoodMove; 
        }
    }

    return NotValidMove; 
}