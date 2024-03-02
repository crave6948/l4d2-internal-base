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
        Module::ModuleManager moduleManager;
        File::FileManager fileManager;
    };
    inline None client;
}