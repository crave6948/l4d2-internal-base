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
        load();
    }
    void FileManager::load()
    {
        // Get the current path
        std::filesystem::path currentPath = std::filesystem::current_path();
        // check if file exists
        std::string filePath = currentPath.string() + "/settings.json";
        if (std::filesystem::exists(filePath))
        {
            nlohmann::json data;
            std::ifstream file(filePath);
            file >> data;
            for (auto module : Client::client.moduleManager.featurelist)
            {
                if (data.contains(module->getName()))
                {
                    auto settings = data[module->getName()];
                    module->setEnabled(settings["enabled"]);
                    module->setKey(settings["key"]);
                    // check if settings["values"] is null
                    if (settings["values"].is_null())
                    {
                        continue;
                    }
                    auto valueList = settings["values"];
                    if (valueList.is_null())
                        continue;
                    for (auto valueData : valueList)
                    {
                        if (valueData.is_null())
                            continue;
                        for (auto it = valueData.begin(); it != valueData.end(); it++)
                        {
                            std::string name = it.key();
                            auto value = module->vManager.GetValue(name);
                            if (value == nullptr)
                                continue;
                            if (auto booleanValue = dynamic_cast<V::BooleanValue *>(value))
                            {
                                //check the value type if it is boolean
                                if (valueData[name].is_boolean())
                                    booleanValue->SetValue(valueData[name]);
                            }
                            else if (auto listValue = dynamic_cast<V::ListValue *>(value))
                            {
                                //check the value type if it is string
                                if (valueData[name].is_string())
                                    listValue->SetSelected(valueData[name]);
                            }
                            else if (auto numberValue = dynamic_cast<V::NumberValue *>(value))
                            {
                                //check the value type if it is integer
                                if (valueData[name].is_number_integer())
                                    numberValue->SetValue(valueData[name]);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            save();
        }
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
        // check if file exists if not it will create a new file with output mode
        if (std::filesystem::exists(filePath))
        {
            std::cout << "File exists" << std::endl;
        }
        else
        {
            // write new file with output mode
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