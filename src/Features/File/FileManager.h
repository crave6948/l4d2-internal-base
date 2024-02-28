//this is the file manager class it will b used to manage features values and save them to a file
// it used json as data format
#include <string>
#include "../../Util/Json/json.hpp"
namespace File {
    class FileManager {
        public:
            FileManager();
            void SaveToFile(std::string path, std::string data);
            std::string ReadFromFile(std::string path);
    };
}