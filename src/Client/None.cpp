#include <WinSock2.h>
#include "crow.h"
#include "None.h"
#include <thread>

namespace Client
{
    void None::initialize()
    {
        moduleManager.Init();
        fileManager.init();
        menu.init();
    }

    inline crow::SimpleApp app;
    inline std::thread serverThread;

    void None::shutdown()
    {
        stop_server = true;
        app.stop();
        fileManager.save();
    }

    void None::setupRoutes()
    {
        // @param name of the module
        // @return module or nullptr
        const auto findModule = [&](std::string name)
        {
            return moduleManager.getFeature(name);
        };
        const auto findValue = [&](Client::Module::Module *it, std::string name)
        {
            return it->vManager.GetValue(name);
        };
        // define your endpoint at the root directory
        CROW_ROUTE(app, "/")
        ([]()
         { return "Hello world"; });
        CROW_ROUTE(app, "/toggle").methods("GET"_method)([&]()
                                                         {
            std::string modulesName = "";
            for (auto it : moduleManager.featurelist)
            {
                std::string name = it->getName();
                modulesName.append(name + "\n");
            }
            return modulesName; 
        });
        CROW_ROUTE(app, "/toggle/<string>").methods("GET"_method)([&](std::string name)
                                                                  {
            auto it = findModule(name);
            if (it == nullptr) return "Not found Module " + name;
            it->toggle();
            return "Toggled " + name + " to " + (it->getEnabled()?  "On" : "Off"); 
        });
        CROW_ROUTE(app, "/keybind/<string>").methods("GET"_method)([&](std::string name)
                                                                   {
            auto it = findModule(name);
            if (it == nullptr) return "Not found Module " + name;                                       
            return "Keybind of " + it->getName() + " is " + std::to_string(it->getKey());
        });
        CROW_ROUTE(app, "/keybind/<string>/<int>").methods("GET"_method)([&](std::string name, int keycode)
                                                                         {
            auto it = findModule(name);
            if (it == nullptr) return "Not found Module " + name;
            it->setKey(keycode);
            return "Set keybind of " + it->getName() + " to " + std::to_string(it->getKey());
        });
        CROW_ROUTE(app, "/module/<string>/values").methods("GET"_method)([&](std::string name)
                                                                         {
            auto it = findModule(name);
            if (it == nullptr) return "Not found Module " + name;
            std::string valuesName = "";
            for (auto value : it->vManager.GetValues())
            {
                valuesName.append(value->GetName() + "\n");
            }
            return valuesName; });
        CROW_ROUTE(app, "/module/value").methods("POST"_method)([&](const crow::request& req)
                                                                                                  {
            // nlohmann::json json = nlohmann::json::parse(req.body);
            crow::json::rvalue json = crow::json::load(req.body);
            
            std::string moduleName = json["ModuleName"].s();
            // auto it = findModule(moduleName);
            // if (it == nullptr) return "Not found Module " + moduleName;
            // std::string valueName = json["ValueName"].s();
            // return "Everything okay" + valueName;
            return moduleName;
            // V::ValueBase* value = findValue(it, valueName);
            // if (value == nullptr) return "Not found Value " + valueName + " in Module " + name;
            // const auto getBoolean = [](std::string value_str) -> bool
            // {
            //     if (value_str == "true")
            //     {
            //         return true;
            //     }
            //     else if (value_str == "false")
            //     {
            //         return false;
            //     }
            //     // if not true or false, return false
            //     return false;
            // };
            // auto bvalue = reinterpret_cast<V::BooleanValue*>(value);
            // return "Set " + valueName + " of " + name + " to " + (bvalue->GetValue() ? "true" : "false"); 
            });
    }

    void None::startServer()
    {
        setupRoutes();
        // crow::SimpleApp app;
        //  app.port(18080).multithreaded().run_async();
        // Create a new thread to run the app
        serverThread = std::thread([&]()
                                   {
                                     // set the port, set the app to run on multiple threads, and run the app
                                     app.port(18080).run(); });

        // Detach the server thread so it runs independently
        serverThread.detach();
    }
}
