#include "FileManager.h"
namespace Client::File
{
    FileManager::FileManager()
    {
    }

    void FileManager::init()
    {
        save();
    }
    void FileManager::save()
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        // Create a JSON object
        nlohmann::json data;
        data["name"] = "John";
        data["age"] = 30;
        data["city"] = "New York";

        // Create an array and add some elements to it
        nlohmann::json hobbies = {"reading", "hiking", "coding"};
        data["hobbies"] = hobbies;

        //file path
        std::string filePath = currentPath.string() + "/output.json";
        // Open the output file
        std::ofstream file(filePath);
        //check if file exists
        if (std::filesystem::exists(filePath))
        {
            std::cout << "File exists" << std::endl;
        }
        else
        {
            file = std::ofstream(filePath, std::ofstream::out);
            std::cout << "File does not exist" << std::endl;
        }
        write_new_file(file, data, true);
    }
    void FileManager::write_new_file(std::ofstream& file, nlohmann::json data, bool overwrite)
    {
        // Check if the file is opened successfully
        if (!file.is_open())
        {
            return;
        }

        // Write JSON data to the file
        file << std::setw(4) << data << std::endl;

        // Close the file
        file.close();
    }
}