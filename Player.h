#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <math.h>
#include "Map.h"


class Player{
    Vector2 position;
    Vector2 direction;
    float angle;

    public:

    static constexpr int SIZE = 16;
    static constexpr float ROTATION_SPEED = 3 * DEG2RAD ;
    static constexpr float MOVEMENT_SPEED = 5 ;

    Player(){
        position = {100,100};
        direction = {1,0};
    }

    Vector2 getPositon() const{
        return position;
    }

    Vector2 getDirection() const{
        return direction;
    }

    float getAngle() const{
        return angle;
    }



    void rotate(){
    if(IsKeyDown(KEY_LEFT)){
        angle -= ROTATION_SPEED;
    }else if(IsKeyDown(KEY_RIGHT)){
        angle += ROTATION_SPEED;
    }

    if(angle > 360 * DEG2RAD){
        angle = 0;
    }
    else if(angle < 0){
        angle = 360 * DEG2RAD;
    }

    direction.x = cos(angle);
    direction.y = sin(angle);
    }

    void move(Map &map){
        if(IsKeyDown(KEY_W)){
            if(map.getMapValue((int)(((position.x + direction.x * MOVEMENT_SPEED) / Map::CELL_SIZE)) , (int)((position.y + direction.y * MOVEMENT_SPEED ) / Map::CELL_SIZE)) == 0 ){
                position.x += direction.x * MOVEMENT_SPEED;
                position.y += direction.y * MOVEMENT_SPEED;
            }
            
        }else if(IsKeyDown(KEY_S)){
            if(map.getMapValue((int)(((position.x - direction.x * MOVEMENT_SPEED) / Map::CELL_SIZE)) , (int)((position.y - direction.y * MOVEMENT_SPEED ) / Map::CELL_SIZE)) == 0 ){
                position.x -= direction.x * MOVEMENT_SPEED;
                position.y -= direction.y * MOVEMENT_SPEED;
            }
        }

        if(IsKeyDown(KEY_A)){
            if(map.getMapValue((int)(((position.x + cos(angle - 90 * DEG2RAD) * MOVEMENT_SPEED) / Map::CELL_SIZE)) , (int)((position.y + sin(angle - 90 * DEG2RAD) * MOVEMENT_SPEED ) / Map::CELL_SIZE)) == 0 ){
            position.x += cos(angle - 90 * DEG2RAD) * MOVEMENT_SPEED;
            position.y += sin(angle - 90 * DEG2RAD) * MOVEMENT_SPEED;
            }

        }else if(IsKeyDown(KEY_D)){
            if(map.getMapValue((int)(((position.x + cos(angle + 90 * DEG2RAD) * MOVEMENT_SPEED) / Map::CELL_SIZE)) , (int)((position.y + sin(angle + 90 * DEG2RAD) * MOVEMENT_SPEED ) / Map::CELL_SIZE)) == 0 ){
            position.x += cos(angle + 90 * DEG2RAD) * MOVEMENT_SPEED;
            position.y += sin(angle + 90 * DEG2RAD) * MOVEMENT_SPEED;
            }
        }
    }
};

#endif