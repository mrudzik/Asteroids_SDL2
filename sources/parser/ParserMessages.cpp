
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
    std::cout
	<< "\n winSize_x: " << _data.winSize_x << " winSize_y: " << _data.winSize_y
    << "\n mapSize_x: " << _data.mapSize_x << " mapSize_y: " << _data.mapSize_y
    << "\n Asteroid Num: " << _data.asteroidNum
	<< "\n Ammo Num: " << _data.ammoNum
    << "\n Ability Probability: " << _data.abilityProbability
	<< "\n Brownian Motion: " << _data.brownianMotion
	<< "\n" << std::endl;
}

void ParserControl::ShowHelp()
{
    std::cout << "usage:\n./asteroids [-window <x_size>x<y_size>] [-map <x_size>x<y_size>]"
    "\n\t\t [-num_asteroids <value>] [-num_ammo <value>]"
    "\n\t\t [-ability_probability <value>] [-brown_motion]"
    "\n\n Parameter Description:"
    "\n Adjust Game window size, x_size for Width, y_size for Height"
    "\n\t -window <x_size>x<y_size>"
	"\n\t Example: -window 800x600"
	"\n\t Limits MIN: " << WINDOW_MINSIZE << " MAX: " << WINDOW_MAXSIZE <<
    "\n\n Adjust Game Map size"
    "\n\t -map <x_size>x<y_size>"
	"\n\t Example: -map 1000x1000"
	"\n\t Limits MIN: " << MAP_MINSIZE << " MAX: " << MAP_MAXSIZE <<
    "\n\n Set Asteroid Count"
    "\n\t -num_asteroids <value>"
	"\n\t Example: -num_asteroids 15"
	"\n\t Limits MIN: " << ASTEROID_COUNT_MIN << " MAX: " << ASTEROID_COUNT_MAX <<
    "\n\n Set Ammo Count"
    "\n\t -num_ammo <value>"
	"\n\t Example: -num_ammo 50"
	"\n\t Limits MIN: " << AMMO_COUNT_MIN << " MAX: " << AMMO_COUNT_MAX <<
    "\n\n Set Ability Probability that would be dropped from asteroids"
    "\n\t -ability_probability <value>"
	"\n\t Example: -ability_probability 0.6"
	"\n\t Limits MIN: " << ABILITY_PROB_MIN << " MAX: " << ABILITY_PROB_MAX <<
	"\n\n Flag to turn on Experimental Brownial Motion in game"
	"\n\t -brown_motion"
    "\n" << std::endl;
}
