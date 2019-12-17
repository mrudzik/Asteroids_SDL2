
#include "ParserControl.hpp"


int ParserControl::ParseSize(int* x_res, int* y_res, std::string param)
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

int ParserControl::ParseCount(int *res, std::string param)
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

int ParserControl::ParseRate(double *res, std::string param)
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
