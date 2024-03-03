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
        Module::ModuleManager moduleManager = Module::ModuleManager();
        File::FileManager fileManager = File::FileManager();
    };
    inline None client = None();
}