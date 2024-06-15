#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../Util/Json/json.hpp"
#include "../ModuleManager/Module/ModuleCategory.h"
namespace Client::File
{
    class FileManager
    {
    private:
        const float auto_load_interval = 1.f;
        const float auto_save_interval = 15.f;
        bool firstload = true;
        void loadCategory(nlohmann::json category, Client::Module::ModuleCategory moduleCategory);
    public:
        float last_load = 0;
        float last_save = 0;
        FileManager();
        void init();
        void load();
        void loadFromJson(std::string jsonData);
        void save();
        void write_new_file(std::ofstream& file, nlohmann::json data, bool overwrite);
        nlohmann::json getData();
        void running_auto_save();
    };
}