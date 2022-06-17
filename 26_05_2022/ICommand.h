#ifndef ICOMMAND_H
#define ICOMMAND_H
#include "App.h"

class ICommand {
public:
    virtual bool validate() = 0;
    virtual void execute() = 0;
    static ICommand* create(App* app);
    virtual ~ICommand() {}
};

#endif
