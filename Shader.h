class ShaderColor{

    Color wall;
    Color wallSide;
    Color flor;
    Color tower;
    Color towerSide;

    float shaderPower;
    float shadeFactor;

public:

        ShaderColor(){
            wall = WHITE;
            wallSide = LIGHTGRAY;
            flor = DARKGRAY;
            tower = RED;
            towerSide = {190,34,46,255};

            shaderPower = 400.0f;
            shadeFactor = 0.0;
        }

        void setColorToStart(){
            wall = WHITE;
            wallSide = LIGHTGRAY;
            flor = DARKGRAY;
        }

        Color getWallShadow(float rayLenght){
            setColorToStart();
            shadeFactor = 1.0f - (rayLenght / shaderPower);
            if(shadeFactor < 0) shadeFactor =0;

            wall.r *= shadeFactor;
            wall.g *= shadeFactor;
            wall.b *= shadeFactor;

            return wall;
        }

        Color getWall() const {
            return wall;
        }


        Color getWallSideShadow(float rayLenght){
            setColorToStart();
            shadeFactor = 1.0f - (rayLenght / shaderPower);

            if(shadeFactor < 0) shadeFactor =0;

            wallSide.r *= shadeFactor;
            wallSide.g *= shadeFactor;
            wallSide.b *= shadeFactor;

            return wallSide; 
        }

        Color getWallSide() const {
            return wallSide;
        }


        Color getTower() const{
            return tower;
        }

        Color getTowerSide() const{
            return towerSide;
        }
        
        
};
 