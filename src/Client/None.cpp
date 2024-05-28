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

    void None::startServer()
    {
        // crow::SimpleApp app;
        // define your endpoint at the root directory
        CROW_ROUTE(app, "/")
        ([]()
         { return "Hello world"; });
        CROW_ROUTE(app, "/toggle").methods("GET"_method)([&]()
        {
            std::string modulesNames = "";
            for (auto it : moduleManager.featurelist)
            {
                std::string name = it->getName();
                modulesNames.append(name + "\n");
            }
            return modulesNames;
        });
        CROW_ROUTE(app, "/toggle/<string>").methods("GET"_method)([&](std::string name)
                                                                  {
            auto it = moduleManager.getFeature(name);
            if (it == nullptr) return "Not found Module " + name;
            it->toggle();
            return "Toggled " + name + " to " + (it->getEnabled()?  "On" : "Off"); });
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
