#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../Util/Json/json.hpp"
namespace Client::File
{
    class FileManager
    {
    private:
        const float auto_save_interval = 5.f;
        int last_save = 0;
    public:
        FileManager();
        void init();
        void load();
        void save();
        void write_new_file(std::ofstream& file, nlohmann::json data, bool overwrite);
        void running_auto_save();
    };
}