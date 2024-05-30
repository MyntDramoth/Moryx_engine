#include "../Game/game.h"
#include <Windows.h>

void Game::run() {
    on_create();
    MSG msg = {};

    while (is_running){
        
        if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
            if(msg.message == WM_QUIT) {
                is_running = false;
                continue;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        on_update_internal();

    }

    on_quit();
}


