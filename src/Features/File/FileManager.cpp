#include "FileManager.h"
#include <iostream>
#include <fstream>
namespace File {
    FileManager::FileManager()
    {
        std::string data[] = { "Hello", "World" };
        std::filesystem::path currentPath = std::filesystem::current_path();
        SaveToFile(currentPath.string(), data);
    }
    void FileManager::SaveToFile(std::string path, std::string data[])
    {
        // Open the file for writing
        std::ofstream file(path + "\\output.txt");

        // Check if the file is opened successfully
        if (!file.is_open()) {
            return;
        }

        // Write data to the file
        for (int i = 0; i < data->size(); i++) {
            file << data[i] << std::endl;
        }

        // Close the file when done
        file.close();
    }
}