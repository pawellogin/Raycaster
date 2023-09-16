class Map{
    const int X = 10;
    const int Y = 10;
    const int size = 64;

    int matrix[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,0,0,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1},     
        };

public:

    Map(){
        //matrix[5][5] = 1;
        //putBlock(5,5);
    }


    float getSize() const{
        return size;
    }

    int getMatrix(int x,int y) const{
        return matrix[x][y];
    }

    void drawMap(){

    const int size = 64;

        for(int i = 0;i<Y;i++){
            for(int j = 0;j<X;j++){
                if(matrix[j][i] == 1){
                DrawRectangle(j*size,i*size,size-1,size-1,DARKGRAY);
                }else{
                DrawRectangle(j*size,i*size,size-1,size-1,LIGHTGRAY);
                }
            }
        }
    }

    void putBlock(int x, int y){
       

        if ((x >= X || x < 0) || (y >= Y || y < 0)) {
            return;
        } else if (matrix[x][y] == 0) {
            matrix[x][y] = 1;
        }

        
    }


};