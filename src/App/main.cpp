#include <iostream>
#include "app_window.h"

int main() {

    App_Window application;
    if(application.init()) {

        while(application.is_running()) {
            application.broadcast();
            
        }

    }


    std::cout<<"engine works!\n";
    return 0;
}