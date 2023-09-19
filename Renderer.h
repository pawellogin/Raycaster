#ifndef RENDERER_H
#define RENDERER_H

#include "Map.h"
#include "Player.h"
#include "Raycaster.h"



class Shadow{

Color gray;


public:

    Shadow(){
        gray = GRAY;

    }

    //shadow power 0.0 - 1.0

    Color makeShadow(Color color,float shadowPower) const{
        
        if(shadowPower > 1) color = {0,0,0,255};


        float shadow = color.r * shadowPower;
        color.r -= shadow;

        shadow = color.g * shadowPower;
        color.g -= shadow;

        shadow = color.b * shadowPower;
        color.b -= shadow;

        
        
        return color;

    }
};



class Renderer{

    const Map& map;
    const Player& player;
    const Raycaster& raycaster;
    Shadow shadow;


    public:

    static constexpr size_t SCREEN_WIDTH = 1366;
    static constexpr size_t SCREEN_HEIGHT = 768;
    const float miniMapScale = 0.3 ;
    const int wallSize = 50;

    Renderer(const Map & map,const Player& player, const Raycaster& raycaster) : map(map),player(player), raycaster(raycaster){
       
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

    void printFloor(){
        Color VERYDARKGREEN = {0,60,22,255};

        DrawRectangleV({0,SCREEN_HEIGHT/2},{SCREEN_WIDTH,SCREEN_HEIGHT / 2},VERYDARKGREEN);
    }

    void printCeling(){
        DrawRectangleV({0,0},{SCREEN_WIDTH,SCREEN_HEIGHT / 2},BLACK);
    }

    void printWalls(){

        float POV = 60.0f;

        float rayAngle = player.getAngle() - (POV/2)*DEG2RAD;

        Vector2 rayDirection = {cos(rayAngle),sin(rayAngle)};

        Vector2 drawPosition = {0.0f,0.0f};

        float rayLenght = 0.0f;
        int side = 0; // 0 vertical, 1 horizontal
        int wall = 0;
        float lineHeight = 0;

        
        for(size_t i = 0; i < SCREEN_WIDTH;i++){

            raycaster.castRay(rayDirection,rayLenght,side,wall);

            lineHeight = ((GetScreenHeight() / rayLenght)*wallSize)  ;
            

            drawPosition.x = i;
            drawPosition.y = (SCREEN_HEIGHT - lineHeight)/2;

            switch(wall){
                case 1:
                    if(side == 0)DrawRectangleV(drawPosition,{1,lineHeight},GRAY);
                    else if(side == 1)DrawRectangleV(drawPosition,{1,lineHeight},DARKGRAY);
                break;

                case 2:

                break;

            }

            
            

            rayAngle += POV / SCREEN_WIDTH * DEG2RAD;
            rayDirection.x = cos(rayAngle);
            rayDirection.y = sin(rayAngle); 
        }
    }

    void printShadowWalls(){

        float POV = 60.0f;

        float rayAngle = player.getAngle() - (POV/2)*DEG2RAD;

        Vector2 rayDirection = {cos(rayAngle),sin(rayAngle)};

        Vector2 drawPosition = {0.0f,0.0f};

        float rayLenght = 0.0f;
        int side = 0; // 0 vertical, 1 horizontal
        int wall = 0;
        float lineHeight = 0;
        float shadowPower = 0;

        for(size_t i = 0; i < SCREEN_WIDTH;i++){

            raycaster.castRay(rayDirection,rayLenght,side,wall);



            lineHeight = ((GetScreenHeight() / rayLenght)*wallSize)  ;
            

            drawPosition.x = i;
            drawPosition.y = (SCREEN_HEIGHT - lineHeight)/2;

            shadowPower = rayLenght / 700;

            switch(wall){
                case 1:
                    if(side == 0)DrawRectangleV(drawPosition,{1,lineHeight},shadow.makeShadow(GRAY,shadowPower));
                    else if(side == 1)DrawRectangleV(drawPosition,{1,lineHeight},shadow.makeShadow(DARKGRAY,shadowPower));
                break;

                case 2:

                break;

            }

            

            rayAngle += POV / SCREEN_WIDTH * DEG2RAD;
            rayDirection.x = cos(rayAngle);
            rayDirection.y = sin(rayAngle); 
        }
    }

};

#endif