#include <iostream>
#include "app_window.h"

int main() {
    try{
        Graphics_Engine::create();
        Input_System::create();
    } catch (...){return -1;}

    
    {
   
    try{

        App_Window application;
        

        while(application.is_running());
           
            
        

    } catch(...){
        Input_System::release();
        Graphics_Engine::release();
        
       
        return -1;
    }

    }

    
    Input_System::release();
    Graphics_Engine::release();
    
    std::cout<<"engine works!\n";
   
    return 0;
}