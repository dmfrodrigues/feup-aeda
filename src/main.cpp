#include "app.h"

int main(){
    App app("data/","clients/clients.txt",
                    "managers/managers.txt",
                    "drivers/drivers.txt",
                    "trucks/trucks.txt",
                    "services/services.txt");
    app.start();
    return 0;
}
