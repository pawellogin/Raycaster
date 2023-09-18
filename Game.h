#include "Renderer.h"

class Game{

Player player;
Map map;
Raycaster raycaster;
Renderer renderer;


public:

Game() : player(),map(),raycaster(map,player),renderer(map,player,raycaster) {
    InitWindow(Renderer::SCREEN_WIDTH,Renderer::SCREEN_HEIGHT, "Raycasting");
    SetTargetFPS(60);
}

void run(){

    while (WindowShouldClose() == false){


        player.move(map);
        player.rotate();

        BeginDrawing();

        ClearBackground(BLACK);


        renderer.printCeling();
        renderer.printFloor();    

        renderer.printMiniMap(0,0);
        renderer.printWalls();

        EndDrawing();
    }

    CloseWindow();
}

};