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
	bool 	brownianMotion;
};

#define WINDOW_MAXSIZE 	2000
#define WINDOW_MINSIZE 	200
#define WINDOW_STANDART	800
#define MAP_MAXSIZE  10000
#define MAP_MINSIZE  1500
#define MAP_STANDART 2000
#define ASTEROID_COUNT_MAX 		50
#define ASTEROID_COUNT_MIN		0
#define ASTEROID_COUNT_STANDART 20
#define AMMO_COUNT_MAX 		50
#define AMMO_COUNT_MIN		1
#define AMMO_COUNT_STANDART	30
#define ABILITY_PROB_MAX		1
#define ABILITY_PROB_MIN		0
#define ABILITY_PROB_STANDART 	0.3

class ParserControl
{
private:
    std::vector<std::string> _params;
    s_ParsedData _data;

    // Declared in ParserTools.cpp
    int ParseSize(int* x_res, int* y_res,
		std::string param);
    int ParseCount(int *res, std::string param);
    int ParseRate(double *res, std::string param);

    // Declared in ParserFlags.cpp
    int Find_WindowSize(
		std::string flag, std::string param);
    int Find_MapSize(
		std::string flag, std::string param);
    int Find_AsteroidCount(
		std::string flag, std::string param);
    int Find_AmmoCount(
		std::string flag, std::string param);
    int Find_AbilityProbability(
		std::string flag, std::string param);
	int Find_BrownianMotion(std::string flag);

public:
    // Declared in ParserControl.cpp
    ParserControl(int argc, char** argv);
    ~ParserControl();
    
    int             StartParsing();
    void 			ParsedDataProtection();
	s_ParsedData    GetParsedData();

    // Declared in ParserMessages.cpp
    void ShowParams();
    void ShowData();
    void ShowHelp();

    


    

};

#endif