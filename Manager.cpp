#include "Manager.h"


void Manager::handleGraphicsMode(Pipe& pipe, const bool isMulti)
{
	char msgToGraphics[BUFFER];
	std::string msgFromGraphics = "";
	if (!isMulti)
	{
		msgFromGraphics = pipe.getMessageFromGraphics();
		while (msgFromGraphics != QUIT)
		{
			// should handle the string the sent from graphics
			// according the protocol. Ex: e2e4           (move e2 to e4)
			// YOUR CODE
			handleConsole(msgFromGraphics);
			printTurn();
			this->_board->printBoard();
			strcpy_s(msgToGraphics, std::to_string(getErrorCode()).c_str()); // msgToGraphics should contain the result of the operation
			// return result to graphics		
			pipe.sendMessageToGraphics(msgToGraphics);
			// get message from graphics
			msgFromGraphics = pipe.getMessageFromGraphics();
		}
	}
	else
	{
		Socket socket;
		std::string move = "";
		std::string ip = "";
		std::cin >> ip;
		if (socket.connectToServer(ip, "8000"))  // Connecting to local server on port 8000
		{
			while (move != QUIT)
			{
				printTurn();
				this->_board->printBoard();
				std::cout << "Enter your move or type 'quit' to exit: ";
				std::cin >> move; //players input
				handleConsole(move);
			}

			socket.closeSocket();  // Close the socket when done
		}
		else
		{
			std::cerr << "Failed to connect to the server!" << std::endl;
		}
	}
}

void Manager::handleMulti()
{
	Socket socket;
	std::string move = "";
	std::string ip = "";
	std::cout << "Server IP: ";
	std::cin >> ip;
	if (socket.connectToServer(ip, PORT))  // Connecting to local server on port 8000
	{
		std::cout << "Waiting to Receive Color.." << std::endl;
		std::string color = socket.receiveData();
		while (move != QUIT)
		{
			if (color[0] == BLACK)
			{
				move = socket.receiveData();
				handleConsole(move);
			}
			do
			{
				printTurn();
				this->_board->printBoard();
				std::cout << "Enter your move or type 'quit' to exit: ";
				std::cin >> move; //players input
				handleConsole(move);
			} while (_errorCode != CheckMove && _errorCode != GoodMove);
			socket.sendData(move);
			printTurn();
			this->_board->printBoard();
			move = socket.receiveData();
			handleConsole(move);
		}

		socket.closeSocket();  // Close the socket when done
	}
	else
	{
		std::cerr << "Failed to connect to the server!" << std::endl;
	}
}

void Manager::handleConsoleMode()
{
	std::string move = "";
	while (move != QUIT)
	{
		printTurn();
		this->_board->printBoard();
		std::cout << "Enter your move or type 'quit' to exit: ";
		std::cin >> move; //players input
		handleConsole(move);
	}
}

void Manager::handleConsole(const std::string& move)
{
	std::string src = " ";
	std::string dest = " ";

		if (isValidMoveInput(move))
		{
			//errorCode = 2;
			//splitting input into src and dest
			src = move.substr(DEST_INDEX, NUM_OF_CHARS_IN_LOCATION);
			dest = move.substr(SRC_INDEX, NUM_OF_CHARS_IN_LOCATION);

			this->_errorCode = manageMove(src, dest);
			if (this->_errorCode == GoodMove || this->_errorCode == CheckMove)
			{
				this->_isWhiteTurn = !this->_isWhiteTurn;
			}
			else if (this->_errorCode == CheckMate)
			{
				std::cout << getCurrentPlayer()->getPlayerColor() << " Won!";
			}
			displayError(this->_errorCode);
		}
		else
		{
			std::cerr << "Invalid Move!" << std::endl;
		}
}

bool Manager::isStillChecked()
{
	int i = 0;
	int j = 0;
	Place kingPlace = this->getCurrentPlayer()->getKing()->getCurrentPlace();
	std::string position = "";
	Piece* piece = nullptr;
	for (i; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			//creating a position
			position = std::string(1, BASE_LETTER_ASCII_VALUE + j) + std::to_string(i + 1);
			piece = this->_board->getPiece(position);

			if (piece && piece->getPieceColor() != (_isWhiteTurn ? WHITE : BLACK))
			{
				if (piece->isValidMove(kingPlace, this->_board, getOpponentPlayer(), getCurrentPlayer()) == CheckMove)
				{
					delete piece;
					return true;
				}
			}
			delete piece;
		}
	}
	return false;
}

int Manager::getErrorCode() const
{
	return this->_errorCode;
}

void Manager::printTurn() const
{
	//pritning turn
	if (_isWhiteTurn)
	{
		std::cout << "Whites turn! " << std::endl;
	}
	else
	{
		std::cout << "Blacks turn! " << std::endl;
	}
}

Player* Manager::getCurrentPlayer()
{
	return _isWhiteTurn ? &this->_players[WHITE_PLAYER] : &this->_players[BLACK_PLAYER];
}

Player* Manager::getOpponentPlayer()
{
	Player* player = nullptr;
	_isWhiteTurn = !_isWhiteTurn;
	player = this->getCurrentPlayer();
	_isWhiteTurn = !_isWhiteTurn;
	return player;
}

Manager::Manager(const std::string& initBoard)
{
	//initalizing board and players
	this->_board = new Board(initBoard);
	this->_gameState = Normal;
	this->_players[BLACK_PLAYER] = Player(BLACK, this->_board);
	this->_players[WHITE_PLAYER] = Player(WHITE, this->_board);
	this->_isWhiteTurn = true;
	//maybe Used Later
}

Manager::~Manager()
{
	delete this->_board;
	delete this->_players[BLACK_PLAYER].getKing();
	delete this->_players[WHITE_PLAYER].getKing();
}

void Manager::displayError(const int errorCode)
{
	switch (errorCode)
	{
	case GoodMove:
		std::cout << "Valid move!" << std::endl;
		break;

	case CheckMove:
		std::cout << "Valid move! opponent is checked!" << std::endl;
		break;

	case NotPlayerPiece:
		std::cout << "Invalid move! there is no player's piece in src block!" << std::endl;
		break;

	case AlreadyHasPiece:
		std::cout << "Invalid move! there is a player's piece in dst block!" << std::endl;
		break;

	case WillBeCheck:
		std::cout << "Invalid move! will make check on current player!" << std::endl;
		break;

	case NotValidIndex:
		std::cout << "Invalid move! invalid index!" << std::endl;
		break;

	case NotValidMove:
		std::cout << "Invalid move! this piece DOES NOT move like this!" << std::endl;
		break;

	case SameDestSrc:
		std::cout << "Invalid move! dst and src are the same!" << std::endl;
		break;

	case CheckMate:
		std::cout << "Valid move! CHECKMATE!" << std::endl;
		break;

	default:
		std::cout << "Unknown error :(" << std::endl;
		break;
	}
}

Player Manager::getBlackPlayer() const
{
	return this->_players[BLACK_PLAYER];
}

Player Manager::getWhitePlayer() const
{
	return this->_players[WHITE_PLAYER];
}
Board& Manager::getBoard() const
{
	return *(this->_board);
}

int Manager::manageMove(const std::string& src, const std::string& dest)
{
	Piece* pieceAtDest = this->_board->getPiece(dest);
	Piece* pieceAtSrc = this->_board->getPiece(src);
	char pieceChar = (pieceAtDest != nullptr) ? pieceAtDest->getType() : EMPTY_PLACE; //if there is a piece at dest, piecechar will hold oit type. other wise it will hole # cuz its empty
	Place destPlace = Place(dest, pieceChar);
	Place srcPlace = (pieceAtSrc != nullptr) ? pieceAtSrc->getCurrentPlace() : Place();
	int code = 0;
	//checking if valid pos
	if (!this->_board->isValidPosition(src))
	{
		delete pieceAtDest;
		delete pieceAtSrc;
		return NotValidIndex;
	}
	//cehcking if piece at src ok
	if (!pieceAtSrc || pieceAtSrc->getPieceColor() != (_isWhiteTurn ? WHITE : BLACK))
	{
		delete pieceAtDest;
		delete pieceAtSrc;
		return NotPlayerPiece;
	}
	//d6 to d5
	code = pieceAtSrc->move(destPlace, this->_board, getCurrentPlayer(), getOpponentPlayer());
	if (code == GoodMove || code == CheckMove)
	{
		//setting the board
		this->_board->setBoard(src, destPlace);
		//setting if its the king d6 d5
		if (std::tolower(pieceAtSrc->getType()) == KING)
		{
			getCurrentPlayer()->getKing()->setCurrentPlace(destPlace);
		}
		if (isDiscoveredAttack(src, dest))
		{
			code = CheckMove;
		}
	}
	//if is still in check
	if (isStillChecked())
	{
		if (code != GoodMove && code != CheckMove)
		{
			this->_board->setBoard(src, destPlace);
		}
		if (std::tolower(pieceAtSrc->getType()) == KING)
		{
			getCurrentPlayer()->getKing()->setCurrentPlace(srcPlace);
		}
		//moving back
		pieceAtSrc->move(srcPlace, this->_board, getCurrentPlayer(), getOpponentPlayer());
		this->_board->setBoard(dest, srcPlace);
		if (pieceChar != EMPTY_PLACE)
		{
			this->_board->setPieceAtBoard(dest, pieceAtDest);
		}
		code = WillBeCheck;
	}
	else
	{
		//deactivating check
		getCurrentPlayer()->deactivateCheck();
		if (getCurrentPlayer()->isChecked())
		{
			code = CheckMove;
		}
	}

	delete pieceAtDest;
	delete pieceAtSrc;
	return code;
}

bool Manager::isValidMoveInput(const std::string& move)
{
	char srcRow = ' ';
	char destRow = ' ';
	char srcLine = ' ';
	char destLine = ' ';
	//checking if length is ok
	if (move.length() != LENGTH)
	{
		return false;
	}
	srcRow = move[SRC_ROW_INDEX];
	destRow = move[DEST_ROW];
	srcLine = move[SRC_LINE];
	destLine = move[DEST_LINE];
	return isalpha(srcRow) && isalpha(destRow) && isdigit(srcLine) && isdigit(destLine);
}
bool Manager::isDiscoveredAttack(const std::string& src, const std::string& dest)
{
	Piece* srcPiece = this->_board->getPiece(src);
	Piece* destPiece = this->_board->getPiece(dest);
	Place srcPlace = srcPiece ? srcPiece->getCurrentPlace() : Place();
	Place destPlace(dest, destPiece ? destPiece->getType() : EMPTY_PLACE);
	bool discoveredAttack = false;
	//this->_board->setBoard(src, destPlace);
	if (srcPiece)
	{
		srcPiece->setCurrentPlace(destPlace);
	}
	//checking if still in check
	_isWhiteTurn = !_isWhiteTurn;
	discoveredAttack = isStillChecked();
	_isWhiteTurn = !_isWhiteTurn;
	//
	this->_board->setBoard(dest, srcPlace);
	//settingg to the src location
	if (srcPiece)
	{
		srcPiece->setCurrentPlace(srcPlace);
	}
	if (destPiece)
	{
		this->_board->setPieceAtBoard(dest, destPiece);
	}
	//freeing memory
	delete destPiece;
	delete srcPiece;
	return discoveredAttack;
}
