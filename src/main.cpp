#include "app.h"

int main(){
    App app("data/","managers/managers.txt",
                    "drivers/drivers.txt",
                    "clients/clients.txt",
                    "trucks/trucks.txt",
                    "services/services.txt");
    app.start();
    return 0;
}
