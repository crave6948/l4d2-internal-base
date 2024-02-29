#include "None.h"

Client::None::None()
{
    initialize();
}

void Client::None::initialize()
{
    moduleManager = Module::ModuleManager();
    fileManager = File::FileManager();
    moduleManager.init();
    fileManager.init();
}