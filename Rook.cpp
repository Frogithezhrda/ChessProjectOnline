#include "Rook.h"

Rook::Rook(const char pieceColor, const Place& firstPlace) : Piece(pieceColor, (pieceColor == WHITE ? RookName : std::toupper(RookName)), firstPlace)
{

}
Rook::~Rook() {}

int Rook::isValidMove(const Place& dest, Board* board, Player* currentPlayer, Player* opponentPlayer) const
{
    char currentRow = this->getCurrentPlace().getRow();
    char currentLine = this->getCurrentPlace().getLine();
    char pieceColor = islower(dest.getCurrentPiece()) ? WHITE : BLACK;
    int code = isBasicValid(dest, board, currentPlayer); //getting the code
    //checking if its a empty place
    if (dest.getCurrentPiece() == EMPTY_PLACE)
    {
        pieceColor = EMPTY_PLACE;
    }
    //checking if its within line or row
    if (isClearPath(dest, this->getCurrentPlace(), board) && !code && (!dest.hasPiece() || pieceColor != this->getPieceColor()) &&
        (currentRow == dest.getRow() || currentLine == dest.getLine()))
    {
        //setting the board
        if (pieceColor != EMPTY_PLACE && std::tolower(dest.getCurrentPiece()) != KING)
        {
            board->setBoard(dest.getLocation(), Place(dest.getLocation(), EMPTY_PLACE));
        }
        //checking for checks
        if (dest.getRow() == opponentPlayer->getKing()->getCurrentPlace().getRow() || dest.getLine() == opponentPlayer->getKing()->getCurrentPlace().getLine())
        {
            if (isClearPath(opponentPlayer->getKing()->getCurrentPlace(), dest, board))
            {
                //activating a check
                opponentPlayer->activateCheck();
                return CheckMove;
            }
        }
        return GoodMove; 
    }
    else if(!code)
    {
        code = NotValidMove;
    }

    return code;
}

bool Rook::isClearPath(const Place& dest, const Place& src, const Board* board) const
{
    //code not nice
    int i = 0;
    int startRow = std::min(src.getLine() - BASE_NUM_ASCII_VALUE, dest.getLine() - BASE_NUM_ASCII_VALUE);
    int endRow = std::max(src.getLine() - BASE_NUM_ASCII_VALUE, dest.getLine() - BASE_NUM_ASCII_VALUE);
    char startLine = std::min(src.getRow(), dest.getRow());
    char endLine = std::max(src.getRow(), dest.getRow());
    char currentRow = src.getRow();
    std::string currentPos = "";
    Piece* currentPiece = nullptr;

    if (currentRow == dest.getRow())  // vertical movement
    {
        for (i = startRow + 1; i < endRow; i++)
        {
            //checking the current piece
            //for each piece if its a clear path
            currentPos = std::string(currentRow + std::to_string(i + 1));
            currentPiece = board->getPiece(currentPos);
            if (currentPiece != nullptr && std::tolower(currentPiece->getType()) != KING)  // check if the square is occupied
            {
                delete currentPiece;
                return false;
            }
            delete currentPiece;
        }
    }
    else if (src.getLine() == dest.getLine())  // horizontal movement
    {
        for (i = startLine + 1; i < endLine; i++)
        {
            //checking currentPiece
            currentPos = std::string(std::string(1, (char)i) + src.getLine());  // hell
            currentPiece = board->getPiece(currentPos);
            if (currentPiece != nullptr)
            {
                delete currentPiece;
                return false;
            }
            delete currentPiece;
        }
    }
    return true; 
}
