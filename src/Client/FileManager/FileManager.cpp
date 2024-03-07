#include "FileManager.h"
#include "../None.h"
#include "../Value/Values/BooleanValue.h"
#include "../Value/Values/ListValue.h"
#include "../Value/Values/NumberValue.h"
#include "../Value/Values/FloatValue.h"
#include "../../SDK/SDK.h"
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
                    // Get values for the module
                    auto values = settings["values"];
                    if (values.is_null())
                        continue;
                    for (auto &value : values)
                    {
                        for (auto &item : value.items())
                        {
                            std::string valueName = item.key(); // Get value name
                            auto valueData = item.value();      // Get value data

                            // Get value object from the module
                            auto valueObject = module->vManager.GetValue(valueName);
                            if (valueObject == nullptr)
                                continue;

                            // Handle different value types
                            std::string type = valueData["type"];
                            if (type == "boolean")
                            {
                                bool boolValue = valueData["value"];
                                // Handle boolean value
                                if (auto booleanValue = dynamic_cast<V::BooleanValue *>(valueObject))
                                {
                                    booleanValue->SetValue(boolValue);
                                }
                            }
                            else if (type == "list")
                            {
                                std::string selectedValue = valueData["value"];
                                // Handle list value
                                if (auto listValue = dynamic_cast<V::ListValue *>(valueObject))
                                {
                                    listValue->SetSelected(selectedValue);
                                }
                            }
                            else if (type == "number")
                            {
                                int numValue = valueData["value"];
                                // Handle number value
                                if (auto numberValue = dynamic_cast<V::NumberValue *>(valueObject))
                                {
                                    numberValue->SetValue(numValue);
                                }
                            }
                            else if (type == "float")
                            {
                                float fValue = valueData["value"];
                                // Handle float value
                                if (auto floatValue = dynamic_cast<V::FloatValue *>(valueObject))
                                {
                                    floatValue->SetValue(fValue);
                                }
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
                    nlohmann::json booleanValueJson;
                    booleanValueJson["type"] = "boolean";
                    booleanValueJson["value"] = booleanValue->GetValue();
                    valueJson[booleanValue->GetName()] = booleanValueJson;
                }
                else if (auto listValue = dynamic_cast<V::ListValue *>(value))
                {
                    nlohmann::json listValueJson;
                    listValueJson["type"] = "list";
                    listValueJson["value"] = listValue->GetSelected();
                    // get all list value
                    nlohmann::json allListJson = nlohmann::json::array();
                    for (auto str : listValue->GetLists())
                    {
                        allListJson.push_back(str);
                    }
                    listValueJson["lists"] = allListJson;
                    valueJson[listValue->GetName()] = listValueJson;
                }
                else if (auto numberValue = dynamic_cast<V::NumberValue *>(value))
                {
                    nlohmann::json numberValueJson;
                    numberValueJson["type"] = "number";
                    numberValueJson["value"] = numberValue->GetValue();
                    // get min and max value
                    numberValueJson["min"] = numberValue->GetMin();
                    numberValueJson["max"] = numberValue->GetMax();
                    // get format
                    numberValueJson["format"] = numberValue->GetFormat();
                    valueJson[numberValue->GetName()] = numberValueJson;
                }
                else if (auto floatValue = dynamic_cast<V::FloatValue *>(value))
                {
                    nlohmann::json floatValueJson;
                    floatValueJson["type"] = "float";
                    floatValueJson["value"] = floatValue->GetValue();
                    // get min and max value
                    floatValueJson["min"] = floatValue->GetMin();
                    floatValueJson["max"] = floatValue->GetMax();
                    // get format
                    floatValueJson["format"] = floatValue->GetFormat();
                    valueJson[floatValue->GetName()] = floatValueJson;
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
        last_save = I::GlobalVars->realtime;
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
    void FileManager::running_auto_save()
    {
        if (I::GlobalVars->realtime - last_save > auto_save_interval)
        {
            load();
            save();
        }
    }
}