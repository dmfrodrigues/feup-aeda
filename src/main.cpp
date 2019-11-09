#include "app.h"

#ifdef _WIN32
    #include <windows.h>
    #include <cstdio>
    #define ENABLEPT()  SetConsoleOutputCP(CP_UTF8)
#else
    #define ENABLEPT()
#endif

int main(){
    ENABLEPT();
    App app("data/","managers/managers.txt",
                    "drivers/drivers.txt",
                    "clients/clients.txt",
                    "trucks/trucks.txt",
                    "services/services.txt");
    app.start();
    return 0;
}
