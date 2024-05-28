#pragma once
#include "ModuleManager/ModuleManager.h"
#include "FileManager/FileManager.h"
#include "Ui/Menu.h"
namespace Client
{
    class None
    {
    public:
        void initialize();
        void shutdown();
        Module::ModuleManager moduleManager = Module::ModuleManager();
        File::FileManager fileManager = File::FileManager();
        Menu::Menu menu = Menu::Menu();

        void startServer();

    private:
        bool stop_server = false;
    };
    inline None client = None();
}