#include "FileManager.h"
#include "../Value/Values/BooleanValue.h"
#include "../Value/Values/ListValue.h"
#include "../Value/Values/NumberValue.h"
#include "../Value/Values/FloatValue.h"
#include "../../SDK/SDK.h"
#include "../None.h"
namespace Client::File
{
    FileManager::FileManager()
    {
    }

    void FileManager::init()
    {
        load();
        firstload = false;
    }
    void FileManager::loadCategory(nlohmann::json category, Client::Module::ModuleCategory moduleCategory)
    {
        for (auto module : Client::client.moduleManager.getFeatureListByCategory(moduleCategory))
        {
            if (category.is_null() || !category.is_array())
            {
                return;
            }
            for (auto moduleObject : category)
            {
                if (moduleObject.is_null())
                {
                    continue;
                }
                if (moduleObject["Name"] == module->getName())
                {
                    auto settings = moduleObject["Settings"];
                    // if (firstload)
                    // {
                        module->setEnabled(settings["enabled"]);
                    // }
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
                    for (auto value : values)
                    {
                        std::string valueName = value["name"]; // Get value name
                        auto valueData = value;                // Get value data

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
                        else if (type == "floatRange")
                        {
                            float min = valueData["value_min"];
                            float max = valueData["value_max"];
                            // Handle floatRange value
                            if (auto floatRangeValue = dynamic_cast<V::FloatRangeValue *>(valueObject))
                            {
                                floatRangeValue->SetValue(min, max);
                            }
                        }else if (type == "color")
                        {
                            nlohmann::json color = valueData["value"];
                            auto colortuple = std::make_tuple(color["r"], color["g"], color["b"], color["a"]);
                            // Handle color value
                            if (auto colorValue = dynamic_cast<V::ColorValue *>(valueObject))
                            {
                                colorValue->SetValue(colortuple);
                            }
                        }
                    }
                }
            }
        }
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
            file.close();
            // load data
            if (data.is_null())
            {
                return;
            }
            if (data.is_array())
            {
                for (auto object : data)
                {
                    if (object.is_null())
                    {
                        continue;
                    }
                    if (object["Category"] == "Combat")
                    {
                        loadCategory(object["Modules"], Client::Module::ModuleCategory::Combat);
                    }
                    else if (object["Category"] == "Visuals")
                    {
                        loadCategory(object["Modules"], Client::Module::ModuleCategory::Visuals);
                    }
                    else if (object["Category"] == "Player")
                    {
                        loadCategory(object["Modules"], Client::Module::ModuleCategory::Player);
                    }
                    else if (object["Category"] == "Misc")
                    {
                        loadCategory(object["Modules"], Client::Module::ModuleCategory::Misc);
                    }
                }
            }
        }
        else
        {
            save();
        }
    }
    void FileManager::loadFromJson(std::string jsonData)
    {
        nlohmann::json data = nlohmann::json::parse(jsonData);
        // load data
        if (data.is_null())
        {
            return;
        }
        if (data.is_array())
        {
            for (auto object : data)
            {
                if (object.is_null())
                {
                    continue;
                }
                if (object["Category"] == "Combat")
                {
                    loadCategory(object["Modules"], Client::Module::ModuleCategory::Combat);
                }
                else if (object["Category"] == "Visuals")
                {
                    loadCategory(object["Modules"], Client::Module::ModuleCategory::Visuals);
                }
                else if (object["Category"] == "Player")
                {
                    loadCategory(object["Modules"], Client::Module::ModuleCategory::Player);
                }
                else if (object["Category"] == "Misc")
                {
                    loadCategory(object["Modules"], Client::Module::ModuleCategory::Misc);
                }
            }
        }
    }
    inline nlohmann::json CategoryToJson(std::string name, Client::Module::ModuleCategory category)
    {
        // get all module in this category
        nlohmann::json featureArray = nlohmann::json::array();
        auto modules = Client::client.moduleManager.getFeatureListByCategory(category);
        for (auto module : modules)
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
                    booleanValueJson["name"] = booleanValue->GetName();
                    booleanValueJson["type"] = "boolean";
                    booleanValueJson["value"] = booleanValue->GetValue();
                    valueJson = booleanValueJson;
                }
                else if (auto listValue = dynamic_cast<V::ListValue *>(value))
                {
                    nlohmann::json listValueJson;
                    listValueJson["name"] = listValue->GetName();
                    listValueJson["type"] = "list";
                    listValueJson["value"] = listValue->GetSelected();
                    // get all list value
                    nlohmann::json allListJson = nlohmann::json::array();
                    for (auto str : listValue->GetLists())
                    {
                        allListJson.push_back(str);
                    }
                    listValueJson["lists"] = allListJson;
                    valueJson = listValueJson;
                }
                else if (auto numberValue = dynamic_cast<V::NumberValue *>(value))
                {
                    nlohmann::json numberValueJson;
                    numberValueJson["name"] = numberValue->GetName();
                    numberValueJson["type"] = "number";
                    numberValueJson["value"] = numberValue->GetValue();
                    // get min and max value
                    numberValueJson["min"] = numberValue->GetMin();
                    numberValueJson["max"] = numberValue->GetMax();
                    // get format
                    numberValueJson["format"] = numberValue->GetFormat();
                    valueJson = numberValueJson;
                }
                else if (auto floatValue = dynamic_cast<V::FloatValue *>(value))
                {
                    nlohmann::json floatValueJson;
                    floatValueJson["name"] = floatValue->GetName();
                    floatValueJson["type"] = "float";
                    floatValueJson["value"] = floatValue->GetValue();
                    // get min and max value
                    floatValueJson["min"] = floatValue->GetMin();
                    floatValueJson["max"] = floatValue->GetMax();
                    // get format
                    floatValueJson["format"] = floatValue->GetFormat();
                    valueJson = floatValueJson;
                }
                else if (auto floatRangeValue = dynamic_cast<V::FloatRangeValue *>(value))
                {
                    nlohmann::json floatRangeValueJson;
                    floatRangeValueJson["name"] = floatRangeValue->GetName();
                    floatRangeValueJson["type"] = "floatRange";
                    floatRangeValueJson["value_min"] = floatRangeValue->GetValue().first;
                    floatRangeValueJson["value_max"] = floatRangeValue->GetValue().second;
                    floatRangeValueJson["maximumrange_min"] = floatRangeValue->GetMaximumRange().first;
                    floatRangeValueJson["maximumrange_max"] = floatRangeValue->GetMaximumRange().second;
                    // get format
                    floatRangeValueJson["format"] = floatRangeValue->GetFormat();
                    valueJson = floatRangeValueJson;
                }else if (auto colorValue = dynamic_cast<V::ColorValue *>(value))
                {
                    nlohmann::json colorValueJson;
                    colorValueJson["name"] = colorValue->GetName();
                    colorValueJson["type"] = "color";
                    nlohmann::json value;
                    auto [r, g, b, a] = colorValue->GetValue();
                    value["r"] = r;
                    value["g"] = g;
                    value["b"] = b;
                    value["a"] = a;
                    colorValueJson["value"] = value;
                    valueJson = colorValueJson;
                }
                allValuesJson.push_back(valueJson);
            }
            settings["values"] = allValuesJson;
            nlohmann::json moduleJson;
            moduleJson["Name"] = module->getName();
            moduleJson["Settings"] = settings;
            featureArray.push_back(moduleJson);
        }
        nlohmann::json categoryJson;
        categoryJson["Category"] = name;
        categoryJson["Modules"] = featureArray;
        return categoryJson;
    }
    void FileManager::save()
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        // Create a JSON object
        nlohmann::json categoryLists = getData();

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
        write_new_file(file, categoryLists, true);
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
    nlohmann::json FileManager::getData()
    {
        nlohmann::json categoryLists = nlohmann::json::array();
        categoryLists.push_back(CategoryToJson("Combat", Client::Module::ModuleCategory::Combat));
        categoryLists.push_back(CategoryToJson("Visuals", Client::Module::ModuleCategory::Visuals));
        categoryLists.push_back(CategoryToJson("Player", Client::Module::ModuleCategory::Player));
        categoryLists.push_back(CategoryToJson("Misc", Client::Module::ModuleCategory::Misc));
        return categoryLists;
    }
    void FileManager::running_auto_save()
    {
        if (I::GlobalVars->realtime - last_load > auto_load_interval)
        {
            // load();
            last_load = I::GlobalVars->realtime;
        }
        else
        {
            if (I::GlobalVars->realtime - last_save > auto_save_interval)
            {
                save();
                last_save = I::GlobalVars->realtime;
            }
        }
    }
}