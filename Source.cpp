/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Manager.h"

#define BUFFER 1024
#define CONSOLE 'c'
#define GRAPHICS 'g'
#define MULTI 'm'

/*
	name: handlemaingame
	input: a pointer to the manager
	output: none
	description: this function handles the main game(asks the player if them want console or graphics and ect)
*/
void handleMainGame(Manager* manager);

/*
	name: handlegraphics
	input: a pointer to the manager
	output: none
	description: this function handles the graphics
*/
void handleGraphics(Manager* manager, const bool isMulti);

int main()
{
	//creating a random using time
	srand(time_t(NULL));
	//creating manager
	Manager* manager = new Manager(INIT_STRING);
	handleMainGame(manager);
	//cleaning manager
	delete manager;
	manager = nullptr;
	return 0;
}


void handleMainGame(Manager* manager)
{
	char type = ' ';
	try
	{
		std::cout << "For Console Game - 'c', For Graphic Game 'g', For Multiplayer 'm': " << std::endl;//choice between graphic and conole
		std::cin >> type;
		if (std::tolower(type) == CONSOLE)//if the player chode console, 
		{
			manager->handleConsoleMode();//call the console
		}
		else if (std::tolower(type) == GRAPHICS)//if the player chose graphics
		{
			handleGraphics(manager, false);//call the menegar
		}
		else if (std::tolower(type) == MULTI)
		{
			manager->handleMulti();//call the menegar
		}
		else//else
		{
			std::cerr << "Invalid input. Exiting program." << std::endl;//error message
		}
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Unknown Exception." << std::endl;//exeptions
	}
}

void handleGraphics(Manager* manager, const bool isMulti)
{
	Pipe p;
	bool isConnect = p.connect();
	std::string ans = "";
	char msgToGraphics[BUFFER];
	//starting the graphic.exe if its in the same folder
	std::cout << "Starting Graphics.exe Just Put It In The Same Folder As The Game" << std::endl;//starting  graphics
	//system("start chessGraphics.exe");

	while (!isConnect)//if graphics dident connect
	{
		std::cout << "cant connect to graphics" << std::endl;
		std::cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << std::endl;
		std::cin >> ans;

		if (ans == TRY_AGAIN)//if they wanted to try again
		{
			std::cout << "trying connect again.." << std::endl;
			Sleep(DELAY);
			isConnect = p.connect();
		}
		else //if they dednt, close the pipe
		{
			p.close();
			return;
		}
	}

	strcpy_s(msgToGraphics, INIT_STRING); // just example...
	p.sendMessageToGraphics(msgToGraphics);   // send the board string
	// get message from graphics
	manager->handleGraphicsMode(p);
	p.close();
}