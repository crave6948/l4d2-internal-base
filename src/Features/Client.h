#pragma once
#include "Manager/Manager.h"
namespace Client {
    class Client {
        public:
            Client();
            F::Manager ModuleManager;
    };
    inline Client client = Client();
}