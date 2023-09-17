#ifndef RENDERER_H
#define RENDERER_H

#include "Map.h"
#include "Player.h"


class Renderer{

    const Map& map;
    const Player& player;


    public:

    static constexpr size_t SCREEN_WIDTH = 1366;
    static constexpr size_t SCREEN_HEIGHT = 768;
    const float miniMapScale = 0.3 ;

    Renderer(const Map & map,const Player& player) : map(map),player(player){
       
    }



    void printMiniMap(float posX, float posY){

        const int printSize = map.CELL_SIZE*miniMapScale;

        size_t i;
        size_t j; 

        for(i=0;i<Map::MAP_HEIGHT;i++){
            for(j=0;j<Map::MAP_WIDTH;j++){
                if(map.getMapValue(j,i)== 1){
                DrawRectangle(j*printSize+posX,i*printSize+posY,printSize-1,printSize-1,DARKGRAY);
                }else{
                DrawRectangle(j*printSize+posX,i*printSize+posY,printSize-1,printSize-1,LIGHTGRAY);
                }
            }
        }



        Vector2 playerPrintPos = player.getPositon();

        playerPrintPos.x = playerPrintPos.x * miniMapScale + posX;
        playerPrintPos.y = playerPrintPos.y * miniMapScale + posY;

        int playerPrintSize = Player::SIZE * miniMapScale;

        DrawCircleV(playerPrintPos,playerPrintSize,RED);

        Vector2 playerPrintDir = playerPrintPos;

        playerPrintDir.x += player.getDirection().x * miniMapScale * 100;
        playerPrintDir.y += player.getDirection().y * miniMapScale * 100;

        DrawLineV(playerPrintPos,playerPrintDir,GREEN);

    }



};

#endif