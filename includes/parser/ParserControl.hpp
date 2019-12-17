#ifndef PARSERCONTROL_HPP
#define PARSERCONTROL_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

struct s_ParsedData
{
    int     winSize_x;
    int     winSize_y;
    int     mapSize_x;
    int     mapSize_y;
    int     asteroidNum;
    int     ammoNum;
    double  abilityProbability;
};

class ParserControl
{
private:
    /* data */
    // int     _argc;
    // char**  _argv;
    std::vector<std::string> _params;
    s_ParsedData _data;

    int Find_WindowSize(std::string flag, std::string param);
    int Find_MapSize(std::string flag, std::string param);
    int Find_AsteroidCount(std::string flag, std::string param);
    int Find_AmmoCount(std::string flag, std::string param);
    int Find_AbilityProbability(std::string flag, std::string param);

public:
    ParserControl(int argc, char** argv);
    ~ParserControl();

    void ShowParams();
    void ShowData();
    void ShowHelp();

    int StartParsing();

    

};





#endif