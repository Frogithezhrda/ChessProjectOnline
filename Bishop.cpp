#include "Bishop.h"
#include "Board.h"
#include "Player.h"

Bishop::Bishop(const char pieceColor, const Place& firstPlace) : Piece(pieceColor, (pieceColor == 'w' ? BishopName : std::toupper(BishopName)), firstPlace)
{

}

Bishop::~Bishop() {}


int Bishop::isValidMove(const Place& dest, Board* board, Player* currentPlayer, Player* opponentPlayer) const
{
    int currentRow = this->getCurrentPlace().getRow() - BASE_LETTER_ASCII_VALUE; //getting the row as number
    int currentColumn = this->getCurrentPlace().getLine() - BASE_NUM_ASCII_VALUE; //getting the line as number
    int destRow = dest.getRow() - BASE_LETTER_ASCII_VALUE;
    int destColumn = dest.getLine() - BASE_NUM_ASCII_VALUE;
    int kingRow = opponentPlayer->getKing()->getCurrentPlace().getRow() - BASE_LETTER_ASCII_VALUE;
    int kingColumn = opponentPlayer->getKing()->getCurrentPlace().getLine() - BASE_NUM_ASCII_VALUE;
    char pieceColor = islower(dest.getCurrentPiece()) ? WHITE : BLACK; //getting current piece color
    int code = isBasicValid(dest, board, currentPlayer);
    //if the destenation is empty, we will set the piece color to #
    if (dest.getCurrentPiece() == EMPTY_PLACE)
    {
        pieceColor = EMPTY_PLACE;
    }
    //if dest isnt diagonally to src, then invalid move.
    if (abs(currentRow - destRow) != abs(currentColumn - destColumn))
    {
        return NotValidMove;
    }
    //if the path is clear or he takes a piece which is a different color
    if (!code && (!dest.hasPiece() || pieceColor != this->getPieceColor()) && isClearPath(dest, this->getCurrentPlace(), board))//if we got an valid code and path is clear and if
    {
        //than settingg thee board to the new ;iece
        if (pieceColor != EMPTY_PLACE && std::tolower(dest.getCurrentPiece()) != KING)
        {
            board->setBoard(dest.getLocation(), Place(dest.getLocation(), EMPTY_PLACE));
        }
        //checking if you can check
        if (abs(destRow - kingRow) == abs(destColumn - kingColumn))
        {
            //checking if we are checking for checks if its the king
            if (std::tolower(dest.getCurrentPiece()) == KING)
            {
                //than you will check with the bishop and king
                if (isClearPath(opponentPlayer->getKing()->getCurrentPlace(),  this->getCurrentPlace(), board))
                {
                    opponentPlayer->activateCheck();
                    return CheckMove;
                }
            }
            //if its not the check of if still in check than you will check if we have a clear path if we have
            else if (isClearPath(opponentPlayer->getKing()->getCurrentPlace(), dest, board))
            {
                //activate check and return checkMove
                opponentPlayer->activateCheck();
                return CheckMove;
            }
        }
        return GoodMove;
    }
    else if (!code)
    {
        code = NotValidMove;
    }

    return code;
}

bool Bishop::isClearPath(const Place& dest, const Place& src, const Board* board) const
{
    //getting rows and colums
    int srcRow = src.getRow() - BASE_LETTER_ASCII_VALUE;//getting the row as number
    int srcCol = src.getLine() - BASE_NUM_ASCII_VALUE;//getting the line as number
    int destRow = dest.getRow() - BASE_LETTER_ASCII_VALUE;
    int destCol = dest.getLine() - BASE_NUM_ASCII_VALUE;
    int rowStep = (destRow > srcRow) ? STEP : BACK_STEP;
    int colStep = (destCol > srcCol) ? STEP : BACK_STEP;
    std::string currentPos = "";
    int currentRow = srcRow + rowStep;
    int currentCol = srcCol + colStep;
    Piece* piece = nullptr;
    if (abs(srcRow - destRow) != abs(srcCol - destCol))//if they arnt in alahcson to each other, then its no even relevent.
    {
        return false;  
    }
    while (currentRow != destRow && currentCol != destCol) 
    {
        //checking if the piece isnt null and if there is a piece
        currentPos = std::string(1, currentRow + BASE_LETTER_ASCII_VALUE) + std::to_string(currentCol + 1);
        piece = board->getPiece(currentPos);
       // if the piece isnt null than there is a piece and the path isnt clear
        if (piece != nullptr) 
        {  
            return false;
        }
        //cleaning memory
        delete piece;
        //countinuing checking
        currentRow += rowStep;
        currentCol += colStep;
    }
    //if no path isnt clear than return that path is clear
    return true;  
}
