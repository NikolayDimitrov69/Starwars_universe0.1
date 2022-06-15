#include <iostream>
#include "App.h"
#include "Jedi.h"
#include "Command.h"
void PrintLogo() {
	std::cout << "         ___________________     ____          ___________\n";
	std::cout << "        /                   |   /    \\        |           \\ \n";
	std::cout << "       /    _______    _____|  /      \\       |    _____   | \n";
	std::cout << "       \\    \\     |    |      /   /\\   \\      |   |_____>  | \n";
	std::cout << "        \\    \\    |    |     /   /__\\   \\     |         __/ \n";
	std::cout << " ________>    |   |    |    /            \\    |   |\\    \\_________ \n";
	std::cout << "|            /    |    |   /    ______    \\   |   | \\             | \n";
	std::cout << "|___________/     |____|  /____/      \\____\\  |___|  \\____________| \n";

	std::cout << " ____    __    ____     ____          ___________      __________\n";
	std::cout << "\\    \\  /  \\  /    /   /    \\        |           \\    /          |\n";
	std::cout << " \\    \\/    \\/    /   /      \\       |    _____   |  /    _______|\n";
	std::cout << "  \\              /   /   /\\   \\      |   |_____>  |  \\    \\ \n ";
	std::cout << "  \\            /   /   /__\\   \\     |         __/    \\    \\ \n";
	std::cout << "    \\    /\\    /   /            \\    |   |\\    \\_______>    |\n";
	std::cout << "     \\  /  \\  /   /    ______    \\   |   | \\               / \n ";
	std::cout << "     \\/    \\/   /____/      \\____\\  |___|  \\_____________/\n";
}

void Exe() {
	App app;

	std::cout << "Enter a one-line command (Type help for more info):\n";

	do {

		app.nextLine();
		ICommand* command = ICommand::create(&app);

		if (command == nullptr)
		{
			std::cout << "Unknown command.\n";
		}
		else
		{
			if (command->validate())
			{
				command->execute();
			}
			delete[] command;// dali?
		}	
		//! Викаме функция, която чисти вектор arguments, по този начин избягваме използването на един и същ аргумент/и няколко пъти.
		app.ArgumentVectorErase();

	} while (true);
}

int main()
{
	PrintLogo();
	Exe();
}
