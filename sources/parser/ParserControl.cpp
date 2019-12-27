
#include "ParserControl.hpp"

ParserControl::ParserControl(int argc, char** argv)// : _argc(argc), _argv(argv)
{
    for (int i = 0; i < argc; i++)
    {
        _params.push_back(argv[i]);
    }
    // ShowParams();

    //  Setup Default Values at Parsed Data
    //  To avoid any problems in future
    //  Parsed data will just override current nums for customization purposes 
    _data.winSize_x = 1600;
    _data.winSize_y = 1000;
    _data.mapSize_x = 2000;
    _data.mapSize_y = 2000;
    _data.asteroidNum = 30;
    _data.ammoNum = 30;
    _data.abilityProbability = 0.3;
}

ParserControl::~ParserControl()
{
    // ShowParams();
}




// TODO Parser Exceptions
int ParserControl::StartParsing()
{
    if (_params.size() == 2)
    {
        if (_params[1].compare("-help") == 0 || _params[1].compare("-h") == 0)
        {
            ShowHelp();
            return 0;
        }
    }

    for (int i = 2; i < (int)_params.size(); i++)
    {// Normal Game Parsing
        // TODO Exception Behaviour
        if (Find_WindowSize(_params.at(i - 1), _params.at(i)) == -1)
            std::cout << "Window param " << i - 1 << " with error" << std::endl;
        if (Find_MapSize(_params.at(i - 1), _params.at(i)) == -1)
            std::cout << "Map param " << i - 1 << " with error" << std::endl;
        
        if (Find_AsteroidCount(_params.at(i - 1), _params.at(i)) == -1)
            std::cout << "Asteroid Count param " << i - 1 << " with error" << std::endl;
        if (Find_AmmoCount(_params.at(i - 1), _params.at(i)) == -1)
            std::cout << "Ammo Count param " << i - 1 << " with error" << std::endl;
        
        if (Find_AbilityProbability(_params.at(i - 1), _params.at(i)) == -1)
            std::cout << "Ability Probability param " << i - 1 << " with error" << std::endl;
    }
    ShowData();
    return 1; // Means to continue Game
}

s_ParsedData ParserControl::GetParsedData()
{
    return _data;
}
