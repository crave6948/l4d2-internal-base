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
        /* data */
    public:
        FileManager();
        void init();
        void save();
        void write_new_file(std::ofstream& file, nlohmann::json data, bool overwrite);
    };
}