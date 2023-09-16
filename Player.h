#include <raylib.h>
#include <cmath>
#include <string>
#include <iostream>
#include "Map.h"
#include "Shader.h"

class Player{
    Vector2 position;
    Vector2 direction;
    float size;
    float angleRadians;
    float rotationSpeed;
    float movementSpeed;

    ShaderColor shader;

    public:
    
    Player(){
        position = {100,100};
        direction = {0,0};
        size = 10;
        angleRadians = 0;
        rotationSpeed = 3 * DEG2RAD;
        movementSpeed = 3;
    }

    void rotate(){
        if(IsKeyDown(KEY_LEFT)){
            angleRadians -= rotationSpeed;
        }else if(IsKeyDown(KEY_RIGHT)){
            angleRadians += rotationSpeed;
        }

        if(angleRadians > 360 * DEG2RAD){
            angleRadians = 0;
        }
        else if(angleRadians < 0){
            angleRadians = 360 * DEG2RAD;
        }

        direction.x = cos(angleRadians);
        direction.y = sin(angleRadians);
    }

    void move(Map map){
        if(IsKeyDown(KEY_W)){
            if(map.getMatrix((int)(((position.x + direction.x * movementSpeed) / map.getSize())) , (int)((position.y + direction.y * movementSpeed ) / map.getSize())) == 0 ){
                position.x += direction.x * movementSpeed;
                position.y += direction.y * movementSpeed;
            }
            
        }else if(IsKeyDown(KEY_S)){
            if(map.getMatrix((int)(((position.x - direction.x * movementSpeed) / map.getSize())) , (int)((position.y - direction.y * movementSpeed ) / map.getSize())) == 0 ){
                position.x -= direction.x * movementSpeed;
                position.y -= direction.y * movementSpeed;
            }
        }

        if(IsKeyDown(KEY_A)){
            if(map.getMatrix((int)(((position.x + cos(angleRadians - 90 * DEG2RAD) * movementSpeed) / map.getSize())) , (int)((position.y + sin(angleRadians - 90 * DEG2RAD) * movementSpeed ) / map.getSize())) == 0 ){
            position.x += cos(angleRadians - 90 * DEG2RAD) * movementSpeed;
            position.y += sin(angleRadians - 90 * DEG2RAD) * movementSpeed;
            }

        }else if(IsKeyDown(KEY_D)){
            if(map.getMatrix((int)(((position.x + cos(angleRadians + 90 * DEG2RAD) * movementSpeed) / map.getSize())) , (int)((position.y + sin(angleRadians + 90 * DEG2RAD) * movementSpeed ) / map.getSize())) == 0 ){
            position.x += cos(angleRadians + 90 * DEG2RAD) * movementSpeed;
            position.y += sin(angleRadians + 90 * DEG2RAD) * movementSpeed;
            }
        }
    }



    void drawPlayer(){
        DrawCircleV(position,size,RED);

        int lenght = 40;

        Vector2 endOfLine = {direction.x*lenght + position.x, direction.y*lenght + position.y};
        DrawLineV(position,endOfLine,BLUE);
    }

    void printVar(){
        std::string angleText = "Angle: " + std::to_string(angleRadians * RAD2DEG);
        DrawText(angleText.c_str(),10,10,20,WHITE);
    }

    Vector2 castRay(Map map,Vector2 dir,float &rayLen,int &side, int &block){
        Vector2 rayStart = position;

        Vector2 rayUnitStepSize = {sqrt(1+(dir.y / dir.x) * (dir.y / dir.x)), sqrt(1+(dir.x / dir.y) * (dir.x / dir.y))};

        Vector2 mapCheck = {(int)position.x,(int)position.y};

        Vector2 rayLenght;

        Vector2 step;

        if(dir.x < 0){
            step.x = -1;
            rayLenght.x = (rayStart.x - (float)mapCheck.x) * rayUnitStepSize.x;
        }
        else{
            step.x = 1;
            rayLenght.x = ((float)(mapCheck.x + 1) - rayStart.x) * rayUnitStepSize.x;
        }
        if(dir.y < 0){
            step.y = -1;
            rayLenght.y = (rayStart.y - (float)mapCheck.y) * rayUnitStepSize.y;
        }
        else{
            step.y = 1;
            rayLenght.y = ((float)(mapCheck.y + 1) - rayStart.y) * rayUnitStepSize.y;
        }

        bool tileFound = false;
        float maxDistance = 1000.0f;
        float distance = 0.0f;

        int axis = 0;

        while(!tileFound && distance < maxDistance){

            if(rayLenght.x < rayLenght.y){
                mapCheck.x +=step.x;
                distance = rayLenght.x;
                rayLenght.x += rayUnitStepSize.x;
                axis = 0;
            }
            else{
                mapCheck.y += step.y;
                distance = rayLenght.y;
                rayLenght.y += rayUnitStepSize.y; 
                axis = 1;            
            }
            

            block = map.getMatrix(mapCheck.x / map.getSize(),mapCheck.y / map.getSize());


            if(map.getMatrix(mapCheck.x / map.getSize(),mapCheck.y / map.getSize()) != 0){
                tileFound = true;

                if(rayLenght.x <= rayLenght.y){
                    rayLen = rayLenght.x;
                    side = axis;
                }else{
                    rayLen = rayLenght.y;
                    side = axis;
                }

                return mapCheck;
            }
        }    
    }

    void drawScreen(Map map){
        float POV = 90.0f;
        float angleRad = angleRadians - (POV/2)*DEG2RAD;

        Vector2 dir = {cos(angleRad),sin(angleRad)};

        Vector2 rayColision = {0.0f,0.0f};

        float rayLenght = 0.0f;
        int side;
        int block=0;
        float lineHeight = 0;
        float drawStart = 0;
        float towerDrawStart = 0.0f;
        float drawEnd = 0;

        int screenHeight = GetScreenHeight();
        int screenWidth = GetScreenWidth();

        //flor
        DrawRectangleV({0,(float)screenHeight/2},{(float)screenWidth,(float)screenHeight},DARKGRAY);

        int w = screenWidth;
        
        for(int i = 0; i < w;i++){
            rayColision = castRay(map,dir,rayLenght,side,block);

            lineHeight = (GetScreenHeight() / rayLenght)*50;
            

            

            drawEnd = lineHeight / 2 + screenHeight / 2;
            if(drawEnd >= screenHeight) drawEnd =  screenHeight - 1;

            


            switch(block){
                case 1:
                    drawStart = - lineHeight /2 + screenHeight / 2 ;
                    if(drawStart < 0 )drawStart = 0;
                    
                    if(side == 0)DrawLineBezier({(float)(i*screenWidth/w),drawStart},{(float)(i*screenWidth/w),drawEnd},screenWidth/w,shader.getWall());
                    else if(side == 1)DrawLineBezier({(float)(i*screenWidth/w),(float)drawStart},{(float)(i*screenWidth/w),(float)drawEnd},screenWidth/w,shader.getWallSide());
                break;

                case 2:
                    towerDrawStart = - lineHeight *2 + screenHeight / 2 ;
                    if(towerDrawStart < 0 )towerDrawStart = 0;

                    if(side == 0)DrawLineBezier({(float)(i*screenWidth/w),(float)towerDrawStart},{(float)(i*screenWidth/w),(float)drawEnd},screenWidth/w,shader.getTower());
                    else if(side == 1)DrawLineBezier({(float)(i*screenWidth/w),(float)towerDrawStart},{(float)(i*screenWidth/w),(float)drawEnd},screenWidth/w,shader.getTowerSide());
                break;

            }
            


            angleRad += POV/w*DEG2RAD;
            dir.x = cos(angleRad);
            dir.y = sin(angleRad); 
        }

    }

    void placeBlock(Map &map){
        int x = (position.x + direction.x * map.getSize())/map.getSize(); 
        int y = (position.y + direction.y * map.getSize())/map.getSize(); 

        map.putBlock(x,y);

    }
};