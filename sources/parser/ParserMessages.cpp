
#include "ParserControl.hpp"

void ParserControl::ShowParams()
{
    for (int i = 0; i < (int)_params.size(); i++)
    {
        std::cout << i << ":|" << _params.at(i) << std::endl;
    }
}

void ParserControl::ShowData()
{
    std::cout << "\n winSize_x: " << _data.winSize_x << " winSize_y: " << _data.winSize_y;
    std::cout << "\n mapSize_x: " << _data.mapSize_x << " mapSize_y: " << _data.mapSize_y;
    std::cout << "\n asteroidNum: " << _data.asteroidNum << " ammoNum: " << _data.ammoNum;
    std::cout << "\n abilityProbability: " << _data.abilityProbability << std::endl;
}

void ParserControl::ShowHelp()
{
    std::cout << "usage:\n./asteroids [-window <x_size>x<y_size>] [-map <x_size>x<y_size>]"
    "\n\t\t [-num_asteroids <value>] [-num_ammo <value>]"
    "\n\t\t [-ability_probability <value>]"
    "\n\n Parameter Description:"
    "\n Adjust Game window size, x_size for Width, y_size for Height"
    "\n\t -window <x_size>x<y_size>\t Example: -window 800x600"
    "\n Adjust Game Map size"
    "\n\t -map <x_size>x<y_size>\t\t Example: -map 1000x1000"
    "\n Set Asteroid Count"
    "\n\t -num_asteroids <value>\t\t Example: -num_asteroids 15"
    "\n Set Ammo Count"
    "\n\t -num_ammo <value> \t\t Example: -num_ammo 50"
    "\n Set Ability Probability that would be dropped from asteroids"
    "\n\t -ability_probability <value> \t Example: -ability_probability 0.6"
    "\n" << std::endl;
}
