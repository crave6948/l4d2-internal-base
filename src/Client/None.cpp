#include "None.h"

Client::None::None()
{
}

void Client::None::initialize()
{
    moduleManager.Init();
    fileManager.init();
    menu.init();
}

void Client::None::shutdown()
{
    fileManager.save();
}
