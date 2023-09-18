#ifndef RAYCASTER_H
#define RAYCASTER_H 

#include "Map.h"
#include "Player.h"

class Raycaster{

    const Map &map;
    const Player &player;

    public:

    Raycaster(const Map &map, const Player &player) :map(map), player(player) {

    }       


    void castRay(Vector2 direction, float &rayLen, int &side, int &wall) const{
        Vector2 rayStartPos = player.getPositon();

        Vector2 rayUnitStepSize = {
            sqrt(1+(direction.y / direction.x) * (direction.y / direction.x)),
            sqrt(1+(direction.x / direction.y) * (direction.x / direction.y))
            };

        Vector2 mapPositionCheck  = {player.getPositon().x,player.getPositon().y};

        Vector2 rayLenght = {0.0f,0.0f};

        Vector2 step = {0.0f,0.0f};

        if(direction.x < 0){
            step.x = -1;
            rayLenght.x = (rayStartPos.x - mapPositionCheck.x) * rayUnitStepSize.x;
        }
        else{
            step.x = 1;
            rayLenght.x = ((mapPositionCheck.x + 1) - rayStartPos.x) * rayUnitStepSize.x;
        }
        if(direction.y < 0){
            step.y = -1;
            rayLenght.y = (rayStartPos.y - mapPositionCheck.y) * rayUnitStepSize.y;
        }
        else{
            step.y = 1;
            rayLenght.y = ((mapPositionCheck.y + 1) - rayStartPos.y) * rayUnitStepSize.y;
        }

        bool tileFound = false;
        float maxDistance = 1000.0f;
        float distance = 0.0f;

        int axis = 0;

        while(!tileFound && distance < maxDistance){

            if(rayLenght.x < rayLenght.y){
                mapPositionCheck.x +=step.x;
                distance = rayLenght.x;
                rayLenght.x += rayUnitStepSize.x;
                axis = 0;
            }
            else{
                mapPositionCheck.y += step.y;
                distance = rayLenght.y;
                rayLenght.y += rayUnitStepSize.y; 
                axis = 1;            
            }
            



            if(map.getMapValue(mapPositionCheck.x / Map::CELL_SIZE,mapPositionCheck.y / Map::CELL_SIZE) != 0){
                tileFound = true;
                
                wall = map.getMapValue(mapPositionCheck.x / Map::CELL_SIZE, mapPositionCheck.y / Map::CELL_SIZE);

                if(rayLenght.x <= rayLenght.y){
                    rayLen = rayLenght.x;
                    side = axis;
                }else{
                    rayLen = rayLenght.y;
                    side = axis;
                }  
            }
        }    
    }

    
};

#endif