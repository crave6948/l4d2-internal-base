#pragma once
#include "ModuleManager/ModuleManager.h"
#include "FileManager/FileManager.h"
namespace Client
{
    class None
    {
    public:
        None();
        void initialize();
        void shutdown();
        Module::ModuleManager moduleManager = Module::ModuleManager();
        File::FileManager fileManager = File::FileManager();
    };
    inline None client = None();
}