#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream> 
#include <algorithm>
#include <cmath>

template <typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[ ";
    for (const auto& element : vec) {
        std::cout << "'" << element << "'" << ", ";
    }
    std::cout << "]" << std::endl;
}

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


std::vector<int> stringToNums(const std::string numString)
{
    std::vector<int> nums;
    for (int i = 0; i < numString.size(); i++)
    {
        char ch = numString[i];
        if (isdigit(ch))
        {
            std::string n{ "" };
            int k{ i };
            while (isdigit(numString[k]) && k < numString.size())
            {
                n += numString[k];
                k++;
            }
            if (n != "")
            {
                nums.push_back(std::stoi(n));
                i = k;
            }

        }
    }
    return nums;
}

int main()
{

    std::ifstream file(".\\external\\input.txt");

    if (!file)
    {
        std::cerr << "File can't be opened!" << std::endl;
        return 1;
    }

    int totalPoints{ 0 };
    while (file)
    {
        std::string line;
        std::getline(file, line);
        std::cout << line << std::endl;
        if (line.empty())
        {
            continue;
        }

        std::string card{ splitString(line, ':')[1] };
        std::string numString{ splitString(card, '|')[0] };
        std::string numWinnersString{ splitString(card, '|')[1] };
        
        std::vector<int> nums{ stringToNums(numString) };
        std::vector<int> winnerNums{ stringToNums(numWinnersString) };

        //printVector(nums);
        //printVector(winnerNums);

        int winners{ 0 };
        for (auto num : nums)
        {
            if(std::find(winnerNums.begin(), winnerNums.end(), num) != winnerNums.end())
            {
                winners++;
            }
        }

        if (winners)
        {
            if (winners == 1)
            {
                totalPoints += 1;
                std::cout << 1 << std::endl;
            }
            else
            {
                totalPoints += std::pow(2, winners - 1);
                std::cout << std::pow(2, winners - 1) << std::endl;
            }
            
        }

    }

    file.close();

    std::cout << "Total: " << totalPoints << std::endl;

    return 0;
}