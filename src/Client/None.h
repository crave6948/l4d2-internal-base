#pragma once
#include "FileManager/FileManager.h"
#include "ModuleManager/ModuleManager.h"
namespace Client
{
    class None
    {
    public:
        None();
        void initialize();
        ModuleManager moduleManager;
        FileManager fileManager;
    };
}