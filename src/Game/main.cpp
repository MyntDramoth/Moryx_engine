#include <iostream>
#include "Game.h"

int main() {
    
    
   
    try{

        Game app;      
        app.run();
           
    } catch(...){
        return -1;
    }

    std::cout<<"engine works!\n";
   
    return 0;
}