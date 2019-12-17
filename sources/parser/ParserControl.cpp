
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
    _data.winSize_x = 800;
    _data.winSize_y = 600;
    _data.mapSize_x = 1000;
    _data.mapSize_y = 1000;
    _data.asteroidNum = 10;
    _data.ammoNum = 30;
    _data.abilityProbability = 0.3;
}

ParserControl::~ParserControl()
{
    // ShowParams();
}

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






int ParseSize(int* x_res, int* y_res, std::string param)
{
    bool num1 = false;
    bool separ = false;
    int separIndex = 0;
    bool num2 = false;

    if (param.size() < 3) // Size Protection
        return -1; // Parameter is to small to work with

    for(int i = 0; i < (int)param.size(); i++)
    {// Lexing Protection
        if (isdigit(param[i]))
        {
            if (num1 == false)
            {// Found first number
                num1 = true;
            }
            else if (separ == true)
            {// If we have separator than second num found
                num2 = true;
            }
        }
        else if (param[i] == 'x')
        {
            if (num1 == false)
                return -1; // separator before any numbers
            else
            {
                if (separ == true)
                    return -1; // we have few separators
                separ = true;
                separIndex = i;
            }
        }
        else
        {
            return -1; // Maybe Character in params
        }
        
    }

    if (!num1 || !separ || !num2 || separIndex == 0) // Is all ok Protection
        return -1; // Something wrong with numbers
    
    //      //      //      //      //      //      //      //      //
    int x_parsed = 0;
    int y_parsed = 0;

    x_parsed = std::atoi(param.c_str());
    param.erase(0, separIndex + 1);
    y_parsed = std::atoi(param.c_str());

    if (x_parsed <= 100 || y_parsed <= 100) // Protection
        return -1; // Invalid Sizes
    
    *x_res = x_parsed;
    *y_res = y_parsed;
    return 1;
}

int ParseCount(int *res, std::string param)
{
    for(int i = 0; i < (int)param.size(); i++)
    {
        if (!isdigit(param.at(i)))
            return -1; // Parameter has characters
    }

    int result = std::atoi(param.c_str());
    if (result < 0)
        return -1; // Wrong Number, only larger than zero will fit 
    *res = result;

    return 1;
}

int ParseRate(double *res, std::string param)
{
    for(int i = 0; i < (int)param.size(); i++)
    {
        char tempCh = param.at(i);
        if (!isdigit(tempCh) && tempCh != '.')
            return -1; // Parameter has wrong characters
    }

    double result = std::atof(param.c_str());
    if (result < 0)
        return -1; // Wrong Number, only larger than zero will fit 
    *res = result;

    return 1;
}


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
