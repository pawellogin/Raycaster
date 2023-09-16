
#include "Player.h"



int main () {
    
    const int screenWidth = 1366;
    const int screenHeight = 768;
    
    Player player;
    Map map;

    InitWindow(screenWidth, screenHeight, "Raycasting");
    SetTargetFPS(60);


    

    

    while (WindowShouldClose() == false){

        player.move(map);
        player.rotate();

        if(IsKeyDown(KEY_SPACE)){
            player.placeBlock(map);
        }  

              
        
        BeginDrawing();

        ClearBackground(BLACK);
        

        player.drawScreen(map);

        //map.drawMap();
        //player.drawPlayer();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}