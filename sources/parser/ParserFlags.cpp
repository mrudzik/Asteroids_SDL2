
#include "ParserControl.hpp"

int ParserControl::Find_WindowSize(std::string flag, std::string param)
{
    if (flag.compare("-window") != 0)
        return 0;
    if (ParseSize(&_data.winSize_x, &_data.winSize_y, param) == -1)
        return -1;
    return 1;
}

int ParserControl::Find_MapSize(std::string flag, std::string param)
{
    if (flag.compare("-map") != 0)
        return 0;
    if (ParseSize(&_data.mapSize_x, &_data.mapSize_y, param) == -1)
        return -1;
    return 1;
}

int ParserControl::Find_AsteroidCount(std::string flag, std::string param)
{
    if (flag.compare("-num_asteroids") != 0)
        return 0;
    if (ParseCount(&_data.asteroidNum, param) == -1)
        return -1;
    return 1;
}

int ParserControl::Find_AmmoCount(std::string flag, std::string param)
{
    if (flag.compare("-num_ammo") != 0)
        return 0;
    if (ParseCount(&_data.ammoNum, param) == -1)
        return -1;
    return 1;
}

int ParserControl::Find_AbilityProbability(std::string flag, std::string param)
{
    if (flag.compare("-ability_probability") != 0)
        return 0;
    if (ParseRate(&_data.abilityProbability, param) == -1)
        return -1;
    return 1;
}