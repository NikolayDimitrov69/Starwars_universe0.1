#ifndef COMMANDS_H
#define COMMANDS_H
#include "ICommand.h"

//! Основни команди:
class CommandOpen : public ICommand
{
private:
    App* app;
public:
    CommandOpen(App* _newapp) {
        app = _newapp;
    }
    virtual bool validate();

    virtual void execute();
};

class CommandClose : public ICommand
{
private:
    App* app;
public:
    CommandClose(App* _newapp) {
        app = _newapp;
    }
    virtual bool validate();

    virtual void execute();
};

class CommandSave : public ICommand
{
private:
    App* app;
public:
    CommandSave(App* _newapp) {
        app = _newapp;
    }
    virtual bool validate();

    virtual void execute();
};

class CommandSaveAs : public ICommand
{
private:
    App* app;
public:
    CommandSaveAs(App* _newapp) {
        app = _newapp;
    }
    virtual bool validate();

    virtual void execute();
};

class CommandHelp : public ICommand
{
private:
    App* app;
public:
    CommandHelp(App* _newapp) {
        app = _newapp;
    }
    virtual bool validate();

    virtual void execute();
};

class CommandExit : public ICommand
{
private:
    App* app;
public:
    CommandExit(App* _newapp) {
        app = _newapp;
    }
    virtual bool validate();

    virtual void execute();
};

//! Джедайски команди:

class CommandAddPlanet : public ICommand
{
private:
    App* app;
    std::string planetarg;
public:
    CommandAddPlanet(App* _newapp) {
        app = _newapp;
        planetarg = "";
    }
    virtual bool validate();

    virtual void execute();
};

class CommandCreateJedi : public ICommand
{
private:
    App* app;
    std::string planetarg;
    std::string namearg;
    unsigned rankarg;
    std::string agearg;
    unsigned saberarg;
    std::string strenghtarg;
public:
    CommandCreateJedi(App* _newapp) {
        app = _newapp;
        planetarg = "";
        namearg = "";
        rankarg = 10;
        agearg = "";
        saberarg = 13;
        strenghtarg = "";
    }
    virtual bool validate();

    virtual void execute();
};

class CommandRemoveJedi : public ICommand
{
private:
    App* app;
    std::string planetarg;
    std::string namearg;
public:
    CommandRemoveJedi(App* _newapp) {
        app = _newapp;
        planetarg = "";
        namearg = "";
    }
    virtual bool validate();

    virtual void execute();
};

class CommandPromoteJedi : public ICommand
{
private:
    App* app;
    double multiplier;
    std::string namearg;
public:
    CommandPromoteJedi(App* _newapp) {
        app = _newapp;
        multiplier = 0;
        namearg = "";
    }
    virtual bool validate();

    virtual void execute();
};

class CommandDemoteJedi : public ICommand
{
private:
    App* app;
    double multiplier;
    std::string namearg;
public:
    CommandDemoteJedi(App* _newapp) {
        app = _newapp;
        multiplier = 0;
        namearg = "";
    }
    virtual bool validate();

    virtual void execute();
};

class CommandGetStrongestJedi : public ICommand
{
private:
    App* app;
    std::string planetarg;
public:
    CommandGetStrongestJedi(App* _newapp) {
        app = _newapp;
        planetarg = "";
    }
    virtual bool validate();

    virtual void execute();
};

class CommandGetYougnestJedi : public ICommand
{
private:
    App* app;
    std::string planetarg;
    unsigned rankarg;
public:
    CommandGetYougnestJedi(App* _newapp) {
        app = _newapp;
        planetarg = "";
        rankarg = 10;
    }
    virtual bool validate();

    virtual void execute();
};

class CommandMostUsedSaberColor : public ICommand
{
private:
    App* app;
    std::string planetarg;
    int rankarg;
public:
    CommandMostUsedSaberColor(App* _newapp) {
        app = _newapp;
        planetarg = "";
        rankarg = 10;
    }
    virtual bool validate();

    virtual void execute();
};

class CommandPrintPlanet : public ICommand
{
private:
    App* app;
    std::string planetarg;
public:
    CommandPrintPlanet(App* _newapp) {
        app = _newapp;
        planetarg = "";
    }
    virtual bool validate();

    virtual void execute();
};

class CommandPrintJedi : public ICommand
{
private:
    App* app;
    std::string namearg;
public:
    CommandPrintJedi(App* _newapp) {
        app = _newapp;
        namearg = "";
    }
    virtual bool validate();

    virtual void execute();
};

class CommandPlanetPlanet : public ICommand
{
private:
    App* app;
    std::string planetarg;
public:
    CommandPlanetPlanet(App* _newapp) {
        app = _newapp;
        planetarg = "";
    }
    virtual bool validate();

    virtual void execute();
};

#endif