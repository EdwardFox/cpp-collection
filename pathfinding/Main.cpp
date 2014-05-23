#include <cstring>
#include "Game.hpp"

void processParameters(const int argc, char* argv[], int& width, int& height) 
{
    for(int i = 1; i < argc; ++i) 
    {
        bool next = (i+1) < argc;    
        
        if(!strcmp(argv[i], "-w") && next) 
            width = atoi(argv[++i]);
            
        if(!strcmp(argv[i], "-h") && next) 
            height = atoi(argv[++i]);
    }
}

int main(int argc, char* argv[])
{
    int width = 640;
    int height = 480;

    if(argc > 1) {
        processParameters(argc, argv, width, height);
    }

    Game game(width, height);
    game.run();
    
    return 0;
}


