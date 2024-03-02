#include "None.h"

Client::None::None()
{
}

void Client::None::initialize()
{
    moduleManager = Module::ModuleManager();
    fileManager = File::FileManager();
    moduleManager.Init();
    fileManager.init();
}