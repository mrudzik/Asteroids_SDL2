
#include "ParserControl.hpp"

ParserControl::ParserControl(int argc, char** argv)// : _argc(argc), _argv(argv)
{
    for (int i = 0; i < argc; i++)
    {
        _params.push_back(argv[i]);
    }

    //  Setup Default Values at Parsed Data
    //  To avoid any problems in future
    //  Parsed data will just override current nums for customization purposes 
    _data.winSize_x = WINDOW_STANDART;
    _data.winSize_y = WINDOW_STANDART;
    _data.mapSize_x = MAP_STANDART;
    _data.mapSize_y = MAP_STANDART;
    _data.asteroidNum = ASTEROID_COUNT_STANDART;
    _data.ammoNum = AMMO_COUNT_STANDART;
    _data.abilityProbability = ABILITY_PROB_STANDART;
	_data.brownianMotion = false;
}

ParserControl::~ParserControl()
{
    // ShowParams();
}

void ParserControl::ParsedDataProtection()
{
	if (_data.winSize_x < WINDOW_MINSIZE || WINDOW_MAXSIZE < _data.winSize_x)
	{// Protection from very large window Sizes
		std::cout << "Parsed Window Width " << _data.winSize_x << " is out of Limits."
		" Setting default size " << WINDOW_STANDART << std::endl;
		_data.winSize_x = WINDOW_STANDART;
	}
	if (_data.winSize_y < WINDOW_MINSIZE || WINDOW_MAXSIZE < _data.winSize_y)
	{// Protection from very large window Sizes
		std::cout << "Parsed Window Height " << _data.winSize_y << " is out of Limits."
		" Setting default size " << WINDOW_STANDART << std::endl;
		_data.winSize_y = WINDOW_STANDART;
	}
	if (_data.mapSize_x < MAP_MINSIZE || MAP_MAXSIZE < _data.mapSize_x)
	{
		std::cout << "Parsed Map Width " << _data.mapSize_x << " is out of Limits."
		" Setting default size " << MAP_STANDART << std::endl;
		_data.mapSize_x = MAP_STANDART;
	}
	if (_data.mapSize_y < MAP_MINSIZE || MAP_MAXSIZE < _data.mapSize_y)
	{
		std::cout << "Parsed Map Height " << _data.mapSize_y << " is out of Limits."
		" Setting default size " << MAP_STANDART << std::endl;
		_data.mapSize_y = MAP_STANDART;
	}
	if (_data.asteroidNum < ASTEROID_COUNT_MIN || ASTEROID_COUNT_MAX < _data.asteroidNum)
	{
		std::cout << "Parsed Asteroid Count " << _data.asteroidNum << " is out of Limits."
		" Setting default count " << ASTEROID_COUNT_STANDART << std::endl;
	}
	if (_data.ammoNum < AMMO_COUNT_MIN || AMMO_COUNT_MAX < _data.ammoNum)
	{
		std::cout << "Parsed Ammo Count " << _data.ammoNum << " is out of Limits."
		" Setting default count " << AMMO_COUNT_STANDART << std::endl;
	}
	if (_data.abilityProbability < ABILITY_PROB_MIN || ABILITY_PROB_MAX < _data.abilityProbability)
	{
		std::cout << "Parsed Ability Probability " << _data.abilityProbability << " is out of Limits."
		" Setting by default " << ABILITY_PROB_STANDART << std::endl;
	}

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

    for (int i = 1; i < (int)_params.size(); i++)
    {// Normal Game Parsing
        // TODO Exception Behaviour
		// Complex Flags with parameters
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
    
		// Simple single Flags with no parameters
		if (Find_BrownianMotion(_params.at(i)) == -1)
			std::cout << "Something wrong at " << i - 1 << std::endl;
	}
	ParsedDataProtection();
    ShowData();
    return 1; // Means to continue Game
}

s_ParsedData ParserControl::GetParsedData()
{
    return _data;
}
