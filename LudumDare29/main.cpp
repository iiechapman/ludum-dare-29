//Ludum Dare 29
//"Beneath the Surface"
//Evan Chapman April 26 2014

#include <SDL2/SDL.h>
#include "Game.h"

#define GAME_WIDTH 1136
#define GAME_HEIGHT 640
#define GAME_TITLE "Ludum Dare 29 - Beneath The Surface"

// ============================================================================


int main(int argc, char* argv[])
{
    if(Game::Instance()->init(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE)){
        
        Game::Instance()->loadData();
        Game::Instance()->start();
        
        while (Game::Instance()->running()) {
            Game::Instance()->run();
            
            Game::Instance()->handleEvents();
            Game::Instance()->update();
            Game::Instance()->render();
            
            //SDL_Delay(5);
        }
        
        cout << "Ending Game\n";
        Game::Instance()->clean();
    }
    
    return 0;
}








































































//END