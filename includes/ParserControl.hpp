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
    std::vector<std::string> _params;
    s_ParsedData _data;

    // Declared in ParserTools.cpp
    int ParseSize(int* x_res, int* y_res, std::string param);
    int ParseCount(int *res, std::string param);
    int ParseRate(double *res, std::string param);

    // Declared in ParserFlags.cpp
    int Find_WindowSize(std::string flag, std::string param);
    int Find_MapSize(std::string flag, std::string param);
    int Find_AsteroidCount(std::string flag, std::string param);
    int Find_AmmoCount(std::string flag, std::string param);
    int Find_AbilityProbability(std::string flag, std::string param);

public:
    // Declared in ParserControl.cpp
    ParserControl(int argc, char** argv);
    ~ParserControl();
    
    int             StartParsing();
    s_ParsedData    GetParsedData();

    // Declared in ParserMessages.cpp
    void ShowParams();
    void ShowData();
    void ShowHelp();

    


    

};

#endif