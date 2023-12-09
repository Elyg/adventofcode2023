#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ranges>

template <typename T>
void printVector(const std::vector<T> &vec) {
    std::cout << "[ ";
    for (const auto& element : vec) {
        std::cout << "'" << element << "'" << ", ";
    }
    std::cout << "]" << std::endl;
}
bool checkNeighs(int idx, int start, int end, int offset, int rows)
{

    int row = floor(idx / offset);
    int col = idx % offset;
    bool isNeigh{ false };

    for (int i=-1; i<=1; ++i)
    {
        for (int j=-1; j<=1; ++j)
        {
            int newRow = row + i;
            int newCol = col + j;
 
            int _idx = idx + j + (i*offset);
            if (_idx == idx)
            {
                continue;
            }

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < offset)
            {
                if (_idx >= start && _idx <= end)
                {
                    std::cout << _idx << std::endl;
                    isNeigh = true;
                    break;

                }
            }
        }
    }
    return isNeigh;
}

struct numData
{
    std::string num = "";
    int start_idx = -1;
    int end_idx = -1;
};


int main()
{

    std::ifstream file(".\\external\\input.txt");

    if (!file)
    {
        std::cerr << "File can't be opened!" << std::endl;
        return 1;
    }

    std::vector<numData> nums;
    std::vector<int> gearLocs;
    int lineId{ 0 };
    int offset{ -1 };
    int totalSum{ 0 };
    while (file)
    {
        std::string line;
        std::getline(file, line);
        //std::cout << line << std::endl;
        if (line.empty())
        {
            continue;
        }
        if (offset == -1)
        {
            offset = line.size();
        }
        for(int i=0; i<line.size(); i++)
        {
            char ch = line[i];
            if (isdigit(ch))
            {
                numData n;
                n.start_idx = i+(offset*lineId);
                int k{ i };
                while (isdigit(line[k]) && k<line.size())
                {
                    n.num += line[k];
                    k++;
                }
                n.end_idx = (k-1)+(offset * lineId);
                std::cout << n.num << " " << n.start_idx << " " << n.end_idx;
                nums.push_back(n);
                i = k;
            }
        }
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '*')
            {
                gearLocs.push_back(i+(offset * lineId));
            }
        }
        lineId++;
        std::cout << std::endl;
 
    }

    file.close();
    std::cout << "Start" << std::endl;
    for (auto idx : gearLocs)
    {
        std::vector<int> adjNums;
        for (auto num : nums)
        {
            bool check{ checkNeighs(idx, num.start_idx, num.end_idx, offset, lineId) };
            if (check)
            {
                adjNums.push_back(std::stoi(num.num));
            }    
        }
        
        if (adjNums.size() == 2)
        {
            totalSum += adjNums[0] * adjNums[1];
        }
    }

    std::cout << "Sum: " << totalSum <<  std::endl;

    return 0;
}