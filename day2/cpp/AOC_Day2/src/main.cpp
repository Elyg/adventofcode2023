#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

std::vector<std::string> splitString(const std::string inputString, const char delimiter) 
{
    std::vector<std::string> elements;

    std::stringstream stream(inputString);
    std::string element;
    while (std::getline(stream, element, delimiter))
    {
        elements.push_back(element);
        //std::cout << element << std::endl;
    }

    return elements;
}

bool isNumber(std::string& str)
{
    bool isNumber = true;
    if (str.empty())
    {
        return false;
    }

    for (int i = 0; str.size(); i++)
    {
        char c = str[i];
        if (!isdigit(c))
        {
            isNumber = false;
        }
    }

    return isNumber;
    
}
void printVector(std::vector<std::string> vec) 
{
    for (auto &ele: vec)
    {
        std::cout << "[" << ele << "]";
    }
    std::cout << std::endl;
}

int main()
{
    std::ifstream file("D:\\Projects\\ProgrammingProjects\\adventofcode2023\\day2\\cpp\\AOC_Day2\\external\\input.txt");

    if (!file)
    {
        std::cerr << "File can't be opened!" << std::endl;
        return 1;
    }
    
    std::unordered_map<std::string, int > totalDice
    {
        // key : (dice, quantity)
        {"red", 12},
        {"green", 13},
        {"blue", 14}
    };

    int gameSum{ 0 };
    while (file)
    {
        std::string line;
        std::getline(file, line);
        std::cout << line << std::endl;
        if (line.empty())
        {
            continue;
        }
        std::vector<std::string> elements{ splitString(line, ';') };
        //printVector(elements);

        std::string gameString{ splitString(elements[0], ':')[0]};
        int gameId = std::stoi(splitString(gameString, ' ')[1]);

        //std::cout << "\t" << gameId << std::endl;
        elements[0] = splitString(elements[0], ':')[1];
        //printVector(elements);

        bool gameValid{ true };
        for (auto& element : elements)
        {
            std::unordered_map<std::string, int > drawDice
            {
                // key : (dice, quantity)
                {"red", 0},
                {"green", 0},
                {"blue", 0}
            };
            std::cout << element;
            std::vector<std::string> splitElement{ splitString(element, ',') };
            //printVector(splitElement);

            for (auto& roll : splitElement)
            {
                std::size_t pos{};
                int rollValue = std::stoi(roll, &pos);
                std::string diceType{ roll.substr(pos+1) };

                drawDice[diceType] += rollValue;

            }

            if (drawDice["red"] > totalDice["red"] || 
                drawDice["green"] > totalDice["green"] ||
                drawDice["blue"] > totalDice["blue"])
            {
                gameValid = false;
            }
            std::cout << " => " << gameValid << std::endl;
        }

        if (gameValid)
        {
            gameSum += gameId;
        }

    }
    
    //std::cout << "red: " << drawDice["red"] << std::endl;
    //std::cout << "green: " << drawDice["green"] << std::endl;
    //std::cout << "blue: " << drawDice["blue"] << std::endl;

    file.close();
    std::cout << gameSum << std::endl;

    return 0;
}