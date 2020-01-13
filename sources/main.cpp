
#include "ParserControl.hpp"
#include "GameManager.hpp"


int    Parsing(int argc, char** argv, s_ParsedData* parsedData)
{
    ParserControl parser(argc, argv);
    if (parser.StartParsing() != 1)
        return 0;

    *parsedData = parser.GetParsedData();
    return 1;
}

int main(int argc, char** argv)
{
    s_ParsedData parsedData;

    if (Parsing(argc, argv, &parsedData) == 0)
        return 0;
    
    GameManager* gameManager = new GameManager(parsedData);
	std::cout << "End of Programm" << std::endl;
    delete gameManager;

}