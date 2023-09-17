#include "Renderer.h"

class Game{

Player player;
Map map;
Renderer renderer;

public:




Game() : player(),map(),renderer(map,player) {
    InitWindow(Renderer::SCREEN_WIDTH,Renderer::SCREEN_HEIGHT, "Raycasting");
    SetTargetFPS(60);
    
}

void run(){

    while (WindowShouldClose() == false){


        player.move(map);
        player.rotate();

        BeginDrawing();

        ClearBackground(BLACK);

        renderer.printMiniMap(0,0);



        EndDrawing();
    }

    CloseWindow();
}

};