#include <raylib.h>
#include <cstddef>



class Game{

static constexpr size_t SCREEN_WIDTH = 1366;
static constexpr size_t SCREEN_HEIGHT = 768;

public:

Game(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting");
    SetTargetFPS(60);
}

void run(){

    while (WindowShouldClose() == false){

              
        
        BeginDrawing();

        ClearBackground(BLACK);


        EndDrawing();
    }

    CloseWindow();
}




};