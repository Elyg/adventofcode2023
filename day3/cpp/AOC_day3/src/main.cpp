#include <fstream>
#include <iostream>
#include <string>
#include <vector>


template <typename T>
void printVector(const std::vector<T> &vec) {
    std::cout << "[ ";
    for (const auto& element : vec) {
        std::cout << "'" << element << "'" << ", ";
    }
    std::cout << "]" << std::endl;
}

int clamp(int value, int minValue, int maxValue) {
    return std::max(minValue, std::min(value, maxValue));
}

int getIndex(int row, int col, int offset) {
    return (row * offset) + col;
}

struct gridData
{
    int offset{ -1 };
    std::vector<char> array{};
} schematic;

std::vector<int> getNeighs(gridData &schematic, int index) {
    
    int rows = schematic.array.size() / schematic.offset;

    int row = floor(index / schematic.offset);
    int col = index % schematic.offset;
    

    std::vector<int> neighs;
    for (int i = -1; i <= 1; ++i) 
    {
        for (int j = -1; j <= 1; ++j) 
        {
            int newRow = row + i;
            int newCol = col + j;

            // Check if the indices are within bounds
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < schematic.offset) 
            {
                int neighborIndex = getIndex(newRow, newCol, schematic.offset);
                if (neighborIndex != index)
                {
                    neighs.push_back(neighborIndex);


                 }

            }
        }
    }

    return neighs;
}


int main()
{

    std::ifstream file(".\\external\\input.txt");

    if (!file)
    {
        std::cerr << "File can't be opened!" << std::endl;
        return 1;
    }


    while (file)
    {
        std::string line;
        std::getline(file, line);
        std::cout << line << std::endl;
        if (line.empty())
        {
            continue;
        }

        if (schematic.offset == -1)
        {
            schematic.offset = int(line.length());
            //std::cout << line.length() << std::endl << std::endl;
        }
        
        for (char ch : line)
        {
            schematic.array.push_back(ch);
        }

        //printVector(schematic.array); 
    }

    file.close();

    int totalSum = 0;
    std::string num{ "" };
    bool numCorrect{ false };
    for (int i = 0; i < schematic.array.size(); i++)
    {
        
        std::vector<int> neighs = getNeighs(schematic, i);
       // for (auto neigh2 : neighs)
        //{
        //    std::cout << neigh2;
        //}
        //std::cout << std::endl;
        
        if (isdigit(schematic.array[i]))
        {
            num += schematic.array[i];


            for (auto neigh : neighs)
            {
                if (schematic.array[neigh] != '.' && isdigit(schematic.array[neigh]) == false)
                {
                    numCorrect = true;
                    break;
                }
            }
            if ((i+1) % schematic.offset != 0 && i != 0)
            {
                continue;
            }
            
            
        }

        //std::cout << num << std::endl;
        if (numCorrect && num != "")
        {
                
            totalSum += std::stoi(num);
            //std::cout << "i: " << i << " " << num << std::endl;

        }
        num = "";
        numCorrect = false; 
        

        if (numCorrect && num != "" && schematic.array.size()-1 == i)
        {

            totalSum += std::stoi(num);

            num = "";
            numCorrect = false;
        }

        
    
    }

    std::cout << "Result: " << std::endl;
    std::cout << totalSum << std::endl;

    return 0;
}