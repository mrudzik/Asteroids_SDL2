
#include "GameSDL_Window.hpp"
#include "ParserControl.hpp"

void LaunchGame()
{
    GameSDL_Window window("Asteroids", 800, 800, 100, 100);

}

#include <iostream>

int main(int argc, char** argv)
{
    ParserControl parser(argc, argv);
    
    parser.StartParsing();


    // std::cout << "Starting Game" << std::endl;
    // LaunchGame();

}