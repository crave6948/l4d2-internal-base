#include "FileManager.h"
#include "../None.h"
#include "../Value/Values/BooleanValue.h"
#include "../Value/Values/ListValue.h"
#include "../Value/Values/NumberValue.h"
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

        nlohmann::json feature;
        for (auto module : Client::client.moduleManager.featurelist)
        {
            nlohmann::json settings;
            settings["enabled"] = module->getEnabled();
            settings["key"] = module->getKey();
            // get all value
            nlohmann::json allValuesJson;
            for (auto value : module->vManager.GetValues())
            {
                nlohmann::json valueJson;
                // Check if value is a BooleanValue class
                if (auto booleanValue = dynamic_cast<V::BooleanValue *>(value))
                {
                    valueJson[booleanValue->GetName()] = booleanValue->GetValue();
                }
                else if (auto listValue = dynamic_cast<V::ListValue *>(value))
                {
                    valueJson[listValue->GetName()] = listValue->GetSelected();
                }
                else if (auto numberValue = dynamic_cast<V::NumberValue *>(value))
                {
                    valueJson[numberValue->GetName()] = numberValue->GetValue();
                }
                else
                {
                    valueJson[value->GetName()] = "None";
                }
                allValuesJson.push_back(valueJson);
            }
            settings["values"] = allValuesJson;
            feature[module->getName()] = settings;
        }

        // file path
        std::string filePath = currentPath.string() + "/settings.json";
        // Open the output file
        std::ofstream file(filePath);
        // check if file exists
        if (std::filesystem::exists(filePath))
        {
            std::cout << "File exists" << std::endl;
        }
        else
        {
            file = std::ofstream(filePath, std::ofstream::out);
            std::cout << "File does not exist" << std::endl;
        }
        write_new_file(file, feature, true);
    }
    void FileManager::write_new_file(std::ofstream &file, nlohmann::json data, bool overwrite)
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