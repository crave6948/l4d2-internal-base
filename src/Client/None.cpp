#include <WinSock2.h>
#define CROW_STATIC_DIRECTORY "None/dist/"
#define CROW_STATIC_ENDPOINT "/<path>"
#include "crow.h"
#include "crow/middlewares/cors.h"
#include "None.h"
#include <thread>
#include <filesystem>
#include <fstream>

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
        // define your endpoint at the root directory
        CROW_ROUTE(app, "/")
        ([]()
         {
            // load html file
            return crow::mustache::load("index.html").render();
        });
        CROW_ROUTE(app, "/getjson").methods("GET"_method)([&]()
                                                          { return fileManager.getData().dump(); });
        CROW_ROUTE(app, "/loadjson").methods("POST"_method)([&](const crow::request &req, crow::response &res)
                                                                          {
            fileManager.loadFromJson(req.body);
            res.code = 200;
            res.body = fileManager.getData().dump();
            res.end(); });
        // Assuming 'app' is your Crow application instance
        CROW_ROUTE(app, "/assets/<path>")
        ([](const crow::request& req, crow::response& res, std::string path){
            std::string basePath = "None/dist/assets"; // Base path to your assets
            // std::string requestedPath = req.url_params.get("path");
            std::string requestedPath = path;

            // Security check: Prevent path traversal attacks
            if (requestedPath.find("..") != std::string::npos) {
                res.code = 404;
                res.end();
            }

            std::string fullPath = basePath + "/" + requestedPath;
            if (std::filesystem::exists(fullPath) && std::filesystem::is_regular_file(fullPath)) {
                res.set_static_file_info(fullPath);
            } else {
                // File not found or is not a regular file
                res.code = 404;
            }
            res.end();
        });
    }

    void None::startServer()
    {
        setupRoutes();
        // Create a new thread to run the app
        serverThread = std::thread([&]()
                                   {
                                     // set the port, set the app to run on multiple threads, and run the app
                                     app.port(18080).run(); });
        // Detach the server thread so it runs independently
        serverThread.detach();
    }
}
