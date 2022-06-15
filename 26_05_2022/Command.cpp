#include "Command.h"

ICommand* ICommand::create(App* app) {
    if (app->getCommand() == "open")
    {
        return new CommandOpen(app);
    }
	else if (app->getCommand() == "close")
	{
		return new CommandClose(app);
	}
	else if (app->getCommand() == "save")
	{
		return new CommandSave(app);
	}
	else if (app->getCommand() == "saveas")
	{
		return new CommandSaveAs(app);
	}
	else if (app->getCommand() == "help")
	{
		return new CommandHelp(app);
	}
	else if (app->getCommand() == "exit")
	{
		return new CommandExit(app);
	}
	else if (app->getCommand() == "add_planet")
	{
		return new CommandAddPlanet(app);
	}
	else if (app->getCommand() == "create_jedi")
	{
		return new CommandCreateJedi(app);
	}
	else if (app->getCommand() == "remove_jedi")
	{
		return new CommandRemoveJedi(app);
	}
	else if (app->getCommand() == "promote_jedi")
	{
		return new CommandPromoteJedi(app);
	}
	else if (app->getCommand() == "demote_jedi")
	{
		return new CommandDemoteJedi(app);
	}
	else if (app->getCommand() == "get_strongest_jedi")
	{
		return new CommandGetStrongestJedi(app);
	}
	else if (app->getCommand() == "get_youngest_jedi")
	{
		return new CommandGetYougnestJedi(app);
	}
	else if (app->getCommand() == "get_most_used_saber_color")
	{
		return new CommandMostUsedSaberColor(app);
	}
	else if (app->getCommand() == "print_planet")
	{
		return new CommandPrintPlanet(app);
	}
	else if (app->getCommand() == "print_jedi")
	{
		return new CommandPrintJedi(app);
	}
	else if (app->PlanetsExists(app->getCommand()))
	{
		return new CommandPlanetPlanet(app);
	}
    else
    {
        return nullptr;
    }
}

bool CommandOpen::validate() {
	if (app->getArgumentSize() != 1)
	{
		std::cout << "Argument error. Corrent usage: open <file_directory>\n";
		return false;
	}
	if (app->getStatus() == "changed")
	{
		std::cout << "You have an open file with unsaved changes, please select close or save first.\n";
		return false;
	}
	if (app->getStatus() == "open")
	{
		std::cout << "Please close the last open file to be able to open a new one.\n";
		return false;
	}
	return true;
}

void CommandOpen::execute() {
	app->setCurrentFile(app->getArgumentNumber(0));
	app->setStatus("open");
	std::cout << "Succsessfully opened " << app->getCurrentFile() << ".\n";
	std::fstream file;
	
	//! Създава файл с въведеното име, ако не съществува. Ползва се апенд, за да не се изтрие съдържанието във файла.
	file.open(app->getCurrentFile() + ".txt", std::ios::app);
	if (file.is_open())
	{
		file.close();
	}

	//! Изчита съдържанието от файл с въведеното име.
	file.open(app->getCurrentFile() + ".txt", std::ios::in);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{

			if (line.substr(0, 5) == "Jedi ")
			{
				Jedi jedi;
				int i = 0;
				std::string token;
				std::istringstream ss(line.substr(5));
				while (std::getline(ss, token, ' ')) {
					i++;
					switch (i)
					{
					case 1: jedi.setPlanet(token);
						break;
					case 2: jedi.setName(token);
						break;
					case 3: jedi.setRank(std::stoi(token));
						break;
					case 4: jedi.setAge(std::stoi(token));
						break;
					case 5: jedi.setSaberColor(std::stoi(token));
						break;
					case 6: jedi.setStrenght(std::stod(token));
						break;
					}
				}	
				app->pushbackJedi(jedi);
			}
			if (line.substr(0, 7) == "Planet ")
			{
				app->pushbackPlanet(line.substr(7));
			}
		}
		file.close();
	}
}

bool CommandClose::validate() {
	if (app->getStatus() == "closed")
	{
		std::cout << "There is no file to close.\n";
		return false;
	}
	return true;
}

void CommandClose::execute() {
	app->setStatus("closed");
	//! Трием вектор planets след като сме го качили във файла, за да избегнем дублиране на информацията при повторно извикване на команда open в същата сесия.
	app->PlanetsVectorErase();
	app->JediVectorErase();
	std::cout << "Successfully closed " << app->getCurrentFile() << ".\n";
}

bool CommandSave::validate() {
	if (app->getStatus() == "closed")
	{
		std::cout << "There is no file to save.\n";
		return false;
	}
	return true;
}

void CommandSave::execute() {
	app->setStatus("open");
	std::fstream file;
	file.open(app->getCurrentFile() + ".txt", std::ios::out);
	if (file.is_open())
	{
		if (app->getPlanetSize() > 0)
		{
			file << app->printPlanetVector();
		}
		if (app->getJediSize() > 0)
		{
			file << app->printJediVector();
		}
		
		file.close();
	}
	std::cout << "Successfully saved " << app->getCurrentFile() << ".\n";
}

bool CommandSaveAs::validate() {
	return CommandSave(app).validate();
}

void CommandSaveAs::execute() {
	app->setCurrentFile(app->getArgumentNumber(0));
	CommandSave(app).execute();
}

bool CommandHelp::validate() {
	return true;
}

void CommandHelp::execute() {
	std::cout << "The following commands are supported:\n"
		"open <file> opens <file>\n"
		"close closes currently opened file\n"
		"save saves the currently open file\n"
		"saveas <file> saves the currently open file in <file>\n"
		"help prints this information\n"
		"exit exists the program\n"
		"add_planet <planet> adds a planet \n"
		"create_jedi <planet> <name> <rank> <age> <saber_color> <strenght> adds a jedi\n"
		"remove_jedi removes <name> <planet> removes a jedi from a selected planet\n"
		"promote_jedi <name> <multiplier> promotes the rank of the jedi by one and increases his strneght\n"
		"demote_jedi <name> <multiplier> demotes the rank of the jedi by one and decreases his strenght\n"
		"get_strongest_jedi <planet> gets the strongest jedi of a planet\n"
		"get_younges_jedi <name> <rank> gest the youngest jedi among given rank\n"
		"get_most_used_saber_color <planet> <rank>(optional)\n"
		"print <planet> prints inhabitants of a planet\n"
		"print <jedi> prints jedi stats\n"
		"<planet> + <planet> prints info about the inhabitants of both planets\n";
}

bool CommandExit::validate() {
	if (app == nullptr)
	{
		return false;
	}
	if (app->getStatus() == "changed")
	{
		std::cout << "You have an open file with unsaved changes, please select close or save first.\n";
		return false;
	}
	return true;
}

void CommandExit::execute() {
	std::cout << "Successfully exited.\n";
	exit(0);
}

bool CommandAddPlanet::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before adding a new planet.\n";
		return false;
	}	
	if (app->getArgumentSize() != 1)
	{
		std::cout << "Argument error. Corrent usage: add_planet <planet_name>\n";
		return false;
	}
	planetarg = app->getArgumentNumber(0);
	if (app->PlanetsExists(planetarg))
	{
		std::cout << "Failed to add planet. Planet " << planetarg << " already exists.\n";
		return false;
	}
	return true;
}

void CommandAddPlanet::execute()
{
	app->setStatus("changed");
	app->pushbackPlanet(planetarg);
	std::cout << "Successfully added planet " << planetarg << ".\n";
}

bool CommandCreateJedi::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before adding a new planet.\n";
		return false;
	}
	if (app->getArgumentSize() != 6)
	{
		std::cout << "Argument error. Corrent usage: create_jedi <planet_name> <name> <rank> <age> <saber_color> <strenght>\n";
		return false;
	}
	planetarg = app->getArgumentNumber(0);
	namearg = app->getArgumentNumber(1);
	rankarg = app->getNumberOfRank(app->getArgumentNumber(2));
	agearg = app->getArgumentNumber(3);
	saberarg = app->getNumberOfColor(app->getArgumentNumber(4));
	strenghtarg = app->getArgumentNumber(5);
	if (rankarg > 7)
	{
		std::cout << "Rank " << app->getArgumentNumber(2) << " does not exist. Possible ranks are - YOUNGLING, INITIATE, PADAWAN, KNIGHT_ASPIRANT, KNIGHT, MASTER, BATTLE_MASTER, GRAND_MASTER.\n";
		return false;
	}
	if (saberarg > 11)
	{
		std::cout << "Color " << app->getArgumentNumber(4) << " is not a cannon color. Possible colors are - blue, yellow, black, red, cyan, magenta, orange, blue-green, brown, white, green, purple.\n";
		return false;
	}
	if (!app->PlanetsExists(planetarg))
	{
		std::cout << "Failed to create Jedi. Planet " << planetarg << " does not exist yet.\n";
		return false;
	}
	if (app->JediExists(namearg))
	{
		std::cout << "Failed to create Jedi. Jedi " << namearg << " already exists.\n";
		return false;
	}
	if (!isNumber(agearg) || std::stoi(agearg) < 0)
	{
		std::cout << "Invalid input for age. Age must be a number higher than 0!\n";
		return false;
	}
	if (!isNumber(strenghtarg) || std::stoi(strenghtarg) < 0)
	{
		std::cout << "Invalid input for strenght. Strenght must be a nubmer higher than 0!\n";
		return false;
	}
	
	return true;
}

void CommandCreateJedi::execute()
{
	Jedi jedi(planetarg, namearg, rankarg, std::stoi(agearg), saberarg, std::stod(strenghtarg));
	app->pushbackJedi(jedi);
	app->setStatus("changed"); 
	std::cout << "Succsessfully added jedi " << namearg << " to planet " << planetarg << ".\n";
}

bool CommandRemoveJedi::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before removing a jedi.\n";
		return false;
	}
	if (app->getArgumentSize() != 2)
	{
		std::cout << "Argument error. Corrent usage: remove_jedi <jedi_name> <planet_name> \n";
		return false;
	}
	planetarg = app->getArgumentNumber(1); 
	namearg = app->getArgumentNumber(0);
	if (!app->PlanetsExists(planetarg))
	{
		std::cout << "Planet " << planetarg << " does not exist.\n";
		return false;
	}
	if (!app->JediExists(namearg))
	{
		std::cout << "Jedi " << namearg << " does not exist.\n";
		return false;
	}
	if (!app->JediExistsOnPlanet(namearg, planetarg))
	{
		std::cout << "Jedi " << namearg << " does not live on planet " << planetarg << ".\n";
		return 0;
	}
	return true;
}

void CommandRemoveJedi::execute()
{
	app->setStatus("changed");
	app->EraseJediNumber(namearg);
	std::cout << "Succsessfully removed jedi " << namearg << ".\n";
}

bool CommandPromoteJedi::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before promoting a jedi.\n";
		return false;
	}
	if (app->getArgumentSize() != 2)
	{
		std::cout << "Argument error. Corrent usage: promote_jedi <jedi_name> <multiplier> \n";
		return false;
	}
	if (!isNumber(app->getArgumentNumber(1)))
	{
		std::cout << "Multiplier must be a positive number of type double!\n";
		return false;
	}
	namearg = app->getArgumentNumber(0);
	multiplier = std::stod(app->getArgumentNumber(1));
	if (!app->JediExists(namearg))
	{
		std::cout << "Jedi " << namearg << " does not exists.\n";
		return false;
	}
	if (!app->canRankIncrease(namearg))
	{
		std::cout << "Jedi " << namearg << " cant be promoted. Max rank reached - GRAND_MASTER.\n";
		return false;
	}
	return true;
}

void CommandPromoteJedi::execute()
{
	app->setStatus("changed");
	app->IncreaseJediRank(namearg, multiplier);
	std::cout << "Jedi " << namearg << " has been successfully promoted!\n";
}

bool CommandDemoteJedi::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before demoting a jedi.\n";
		return false;
	}
	if (app->getArgumentSize() != 2)
	{
		std::cout << "Argument error. Corrent usage: demote_jedi <jedi_name> <multiplier> \n";
		return false;
	}
	if (!isNumber(app->getArgumentNumber(1)))
	{
		std::cout << "Multiplier must be a positive number of type double!\n";
		return false;
	}
	namearg = app->getArgumentNumber(0);
	multiplier = std::stod(app->getArgumentNumber(1));
	if (!app->JediExists(namearg))
	{
		std::cout << "Jedi " << namearg << " does not exists.\n";
		return false;
	}
	if (!app->canRankDecrease(namearg))
	{
		std::cout << "Jedi " << namearg << " cant be demoted. Min rank reached - YOUNGLING.\n";
		return false;
	}
	return true;
}

void CommandDemoteJedi::execute()
{
	app->setStatus("changed");
	app->DecreaseJediRank(namearg, multiplier);
	std::cout << "Jedi " << namearg << " has been successfully demoted!\n";
}

bool CommandGetStrongestJedi::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before using this command.\n";
		return false;
	}
	if (app->getArgumentSize() != 1)
	{
		std::cout << "Argument error. Corrent usage: get_strongest_jedi <planet> \n";
		return false;
	}
	planetarg = app->getArgumentNumber(0);
	if (!app->PlanetsExists(planetarg))
	{
		std::cout << "Planet " << planetarg << " does not exist.\n";
		return false;
	}
	if (!app->PlanetIsInahbitet(planetarg))
	{
		std::cout << "Planet " << planetarg << " is not inhabitet by any jedi.\n";
		return false;
	}
	return true;
}

void CommandGetStrongestJedi::execute()
{
	std::cout << "Strongest jedi on planet " << planetarg << " is " << app->GetStrongestJedi(planetarg) << ".\n";
}

bool CommandGetYougnestJedi::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before using this command.\n";
		return false;
	}
	if (app->getArgumentSize() != 2)
	{
		std::cout << "Argument error. Corrent usage: get_youngest_jedi <planet> <rank> \n";
		return false;
	}
	planetarg = app->getArgumentNumber(0);
	rankarg = app->getNumberOfRank(app->getArgumentNumber(1));
	if (rankarg > 7 || rankarg < 0)
	{
		std::cout << "Rank " << app->getArgumentNumber(1) << " does not exist. Possible ranks are - YOUNGLING, INITIATE, PADAWAN, KNIGHT_ASPIRANT, KNIGHT, MASTER, BATTLE_MASTER, GRAND_MASTER.\n";
		return false;
	}
	if (!app->PlanetsExists(planetarg))
	{
		std::cout << "Planet " << planetarg << " does not exist.\n";
		return false;
	}
	if (!app->PlanetIsInahbitet(planetarg))
	{
		std::cout << "Planet " << planetarg << " is not inhabitet by any jedi.\n";
		return false;
	}
	return true;
}

void CommandGetYougnestJedi::execute()
{
	std::cout << "Youngest jedi on planet " << planetarg << " and of rank " << app->getArgumentNumber(1) << " is " << app->GetYoungestJedi(planetarg, rankarg) << ".\n";
}

bool CommandMostUsedSaberColor::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before using this command.\n";
		return false;
	}
	if (app->getArgumentSize() > 2 || app->getArgumentSize() < 1)
	{
		std::cout << "Argument error. Corrent usage: get_most_used_saber_color <planet> <rank>(optional) \n";
		return false;
	}
	planetarg = app->getArgumentNumber(0);
	app->getArgumentSize() == 2 ? rankarg = app->getNumberOfRank(app->getArgumentNumber(1)) : rankarg = -1;
	if ((rankarg > 7 || rankarg < 0) && (!app->getArgumentSize() == 1 && rankarg == -1))
	{
		std::cout << "Rank " << app->getArgumentNumber(1) << " does not exist. Possible ranks are - YOUNGLING, INITIATE, PADAWAN, KNIGHT_ASPIRANT, KNIGHT, MASTER, BATTLE_MASTER, GRAND_MASTER.\n";
		return false;
	}
	if (!app->PlanetsExists(planetarg))
	{
		std::cout << "Planet " << planetarg << " does not exist.\n";
		return false;
	}
	if (!app->PlanetIsInahbitet(planetarg))
	{
		std::cout << "Planet " << planetarg << " is not inhabitet by any jedi.\n";
		return false;
	}
	if (rankarg == -1 && !app->planetHasAGrandMaster(planetarg))
	{
		std::cout << "Planet " << planetarg << " has no jedi of rank GRAND_MASTER living on it.\n";
		return false;
	}
	return true;
}

void CommandMostUsedSaberColor::execute()
{
	if (rankarg == -1)
	{
		std::cout << "Most used color on planet " << planetarg << " that is used by atleast one GRAND_MASTER is " << app->getMostUsedColor(planetarg, rankarg) << ".\n";
	}
	else
	{
		std::cout << "Most used color on planet " << planetarg << " and among jedi of rank " << app->getArgumentNumber(1) << " is " << app->getMostUsedColor(planetarg, rankarg) << ".\n";
	}

}

bool CommandPrintPlanet::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before using this command.\n";
		return false;
	}
	if (app->getArgumentSize() != 1)
	{
		std::cout << "Argument error. Corrent usage: print_planet <planet>\n";
		return false;
	}
	planetarg = app->getArgumentNumber(0);
	if (!app->PlanetsExists(planetarg))
	{
		std::cout << "Planet " << planetarg << " does not exist.\n";
		return false;
	}
	if (!app->PlanetIsInahbitet(planetarg))
	{
		std::cout << "Planet " << planetarg << " is not inhabitet.\n";
		return false;
	}
	return true;
}

void CommandPrintPlanet::execute()
{
	std::cout << "Inhabitants of planet " << planetarg << ":\n"; app->PrintInhabitants(planetarg);
}

bool CommandPrintJedi::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before using this command.\n";
		return false;
	}
	if (app->getArgumentSize() != 1)
	{
		std::cout << "Argument error. Corrent usage: print_jedi <jedi>\n";
		return false;
	}
	namearg = app->getArgumentNumber(0);
	if (!app->JediExists(namearg))
	{
		std::cout << "Jedi " << namearg << " does not exist.\n";
		return false;
	}
	return true;
}

void CommandPrintJedi::execute()
{
	Jedi jedi = app->getJedi(namearg);
	std::cout << "Planet: " << jedi.getPlanet() 
			  << "\nName: " << jedi.getName() 
			  << "\nRank: " << jedi.getRankName(jedi.getRank()) 
			  << "\nAge: " << jedi.getAge() 
			  << "\nSaber Color: " << jedi.getSaberColorName(jedi.getSaberColor()) 
			  << "\nStrenght: " << jedi.getStrenght() << '\n';
}

bool CommandPlanetPlanet::validate()
{
	if (app->getStatus() == "closed")
	{
		std::cout << "You must first open a file before using this command.\n";
		return false;
	}
	if (app->getArgumentSize() != 1)
	{
		std::cout << "Argument error. Corrent usage: <planet> <planet>\n";
		return false;
	}
	planetarg = app->getArgumentNumber(0);
	if (!app->PlanetsExists(planetarg))
	{
		std::cout << "Planet " << planetarg << " does not exist.\n"; 
		return false;
	}
	if (!app->PlanetIsInahbitet(app->getCommand()))
	{
		std::cout << "Planet " << app->getCommand() << " is not inhabitet\n";
		return false;
	}
	if (!app->PlanetIsInahbitet(planetarg))
	{
		std::cout << "Planet " << planetarg << " is not inhabitet.\n";
		return false;
	}
	return true;
}

void CommandPlanetPlanet::execute()
{
	std::cout << "Inhabitants of planet " << app->getCommand() << " and " << planetarg << " sorted alphabeticaly:\n"; app->PrintInhabitants2(app->getCommand(), planetarg);
}
