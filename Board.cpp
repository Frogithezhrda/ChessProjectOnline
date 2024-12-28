#include "Board.h"


Board::Board(const std::string& initBoard)
{
	// getting the last value of the board to go from a8 down
	int i = BOARD_SIZE - 1;
	int j = 0;
	//initialzing Places with correct locations
	for (i; i >= 0; i--)
	{
		//allocating memory
		this->_board[i] = new Place[BOARD_SIZE];
		for(j = 0; j < BOARD_SIZE; j++)
		{
			//
			this->_board[i][j] = Place(char(j + A_ASCII_VALUE) + std::to_string(i + 1), initBoard[i * BOARD_SIZE + j]);
			if (initBoard[i * BOARD_SIZE + j] != EMPTY_PLACE)
			{
				this->_board[i][j].activePiece();
			}
		}
	}
}

Board::~Board()
{
	int i = 0;
	//cleaning the board values of each part of the array
	for (i; i < BOARD_SIZE; i++)
	{
		delete[] _board[i];
	}
}
Piece* Board::getPiece(const std::string& pieceLocation) const
{
	char pieceLetter = ' ';
	Piece* piece = nullptr;
	Place* place = nullptr;
	int row = pieceLocation[ROW_INDEX] - '1'; 
	int col = pieceLocation[COLUM_INDEX] - 'a'; 

	if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) //if row and col are valid...
	{
		place = &_board[row][col];
	}
				pieceLetter = place->getCurrentPiece();//the typemof piece in the givven location
				switch (std::tolower(pieceLetter))
				{
					case PawnName://if the piece is a pawn
						piece = new Pawn(std::islower(pieceLetter) ? WHITE : BLACK, *place);
						break;
					case KnightName://if the piece is a knight
						piece = new Knight(std::islower(pieceLetter) ? WHITE : BLACK, *place);
						break;
					case RookName://if the piece is a rook
						piece = new Rook(std::islower(pieceLetter) ? WHITE : BLACK, *place);
						break;
					case KingName://if the piece is a king
						piece = new King(std::islower(pieceLetter) ? WHITE : BLACK, *place);
						break;
					case BishopName://if the piece is a bishop
						piece = new Bishop(std::islower(pieceLetter) ? WHITE : BLACK, *place);
						break;
					case QueenName://if the piece is a queen
						piece = new Queen(std::islower(pieceLetter) ? WHITE : BLACK, *place);
						break;
				}
				return piece;//returning tthe piece :)
}
void Board::printBoard() const
{
	int i = BOARD_SIZE - 1;
	int j = 0;
	//going through each place in the board and printing it
	for (i; i >= 0; i--)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			std::cout << this->_board[i][j].getCurrentPiece() << ' ';
		}
		std::cout << std::endl;
	}
}

void Board::setBoard(const std::string& src, const Place& dest)
{
	int i = 0;
	int j = 0;

	char movingPieceChar = ' '; 
	bool srcFound = false;

	for (i = 0; i < BOARD_SIZE; i++)//going alll over the board
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (src == this->_board[i][j].getLocation())//if we found the src
			{
				movingPieceChar = this->_board[i][j].getCurrentPiece();
				//there is nothing in rcc anymore cuz we moving it to dest
				this->_board[i][j].setPiece('#'); 
				this->_board[i][j].deactivePiece();

				srcFound = true;//the src was foundd
				break;
			}
		}
		if (srcFound) break;
	}

	for (i = 0; i < BOARD_SIZE; i++)//thrugh the whoolleeee board
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (dest.getLocation() == this->_board[i][j].getLocation())//if we found the dest
			{
				//setting the piece to dest
				this->_board[i][j] = dest;
				this->_board[i][j].setPiece(movingPieceChar);
				this->_board[i][j].activePiece();
				return;
			}
		}
	}
}
Place* Board::getBoard() const
{
	return *(this->_board);
}

bool Board::isValidPosition(const std::string& position) const
{
	char row = position[COLUM_INDEX];
	char column = position[ROW_INDEX];



	if ((row >= FIRST_COLUM_INDEX && row <= LAST_COLUM_INDEX) && (column >= FIRST_ROW_INDEX && column <= LAST_ROW_INDEX))//if the row and colum is in the valid range, then return true
	{
		return true; 
	}
	//otherwise false
	return false; 
}

void Board::setPieceAtBoard(const std::string& dest, Piece* piece)
{
	Place* place = nullptr;
	int row = dest[ROW_INDEX] - '1';
	int col = dest[COLUM_INDEX] - 'a';

	if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) //if the row and col are valid, then inits the piece at given dest
	{
		place = &_board[row][col];
		place->setPiece(piece->getType());
		place->activePiece();
	}

}