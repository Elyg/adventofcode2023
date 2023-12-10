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
struct cardStruct
{
    int cardId = 0;
    int winnerCount = 0;
    std::vector<int> nums;
    std::vector<int> winnerNums;
};

int traverseCards(const std::vector<cardStruct>& vec, cardStruct card)
{
    int sum{ 0 };
    int cardId{ card.cardId };
    int winnerCount{ card.winnerCount };

    if (winnerCount == 0)
    {
        return 1;
    }


    if (winnerCount >= 1)
    {
        for (int i = cardId; i < cardId + winnerCount; ++i)
        {
            sum += traverseCards(vec, vec[i]);
        }
        sum += 1;
    }

    return sum;
}




int main()
{

    std::ifstream file(".\\external\\input.txt");

    if (!file)
    {
        std::cerr << "File can't be opened!" << std::endl;
        return 1;
    }

    std::vector<cardStruct> cards;
    while (file)
    {
        std::string line;
        std::getline(file, line);
        //std::cout << line << std::endl;
        if (line.empty())
        {
            continue;
        }

        int cardId{ stringToNums(splitString(line, ':')[0])[0]};
        std::string card{ splitString(line, ':')[1] };
        std::string numString{ splitString(card, '|')[0] };
        std::string numWinnersString{ splitString(card, '|')[1] };
        
        std::vector<int> nums{ stringToNums(numString) };
        std::vector<int> winnerNums{ stringToNums(numWinnersString) };


        int winners{ 0 };
        for (auto num : nums)
        {
            if(std::find(winnerNums.begin(), winnerNums.end(), num) != winnerNums.end())
            {
                winners++;
            }
        }

        cardStruct c;
        c.cardId = cardId;
        c.winnerCount = winners;
        c.nums = nums;
        c.winnerNums = winnerNums;

        cards.push_back(c);
    }

    file.close();

    std::cout << cards.size() << ": " << std::endl;

    int sum{ 0 };
    for (auto card : cards)
    {
        sum += traverseCards(cards, card);
        //std::cout << card.cardId << ": " << card.winnerCount << std::endl;
    }
    //sum += cards.size();

    std::cout << "Total: " << sum << std::endl;

    return 0;
}