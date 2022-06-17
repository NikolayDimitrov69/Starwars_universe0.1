#include "ICommand.h"
#include "Commands.h"

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
