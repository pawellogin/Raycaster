#ifndef MAP_H
#define MAP_H


#include <raylib.h>
#include <cstddef>
#include <vector>
#include <iostream>



class Map{

    

    public:

    static constexpr size_t CELL_SIZE = 64;
    static constexpr size_t MAP_WIDTH = 12;
    static constexpr size_t MAP_HEIGHT = 12;

    int gameMap[MAP_WIDTH][MAP_HEIGHT]= {
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,0,0,1},
        {1,1,0,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1},
    }; 

    

    Map(){
        

    }

    int getMapValue(size_t x, size_t y) const {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return gameMap[x][y];
    } else {
        std::cerr << "Invalid coordinates: x=" << x << ", y=" << y << std::endl;
        return -1;
    }
}


};

#endif
