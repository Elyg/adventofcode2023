#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <array>

int main()
{
    //std::string filePath{ };
    std::ifstream file("D:\\Projects\\ProgrammingProjects\\adventofcode2023\\day1\\cpp\\AOC_Day1\\external\\input2.txt");

    if (!file)
    {
        std::cerr << "File can't be opened!" << std::endl;
        return 1;
    }

    int sum{ 0 };
    int k = 0;
    while (file)
    {
        std::string line;
        std::getline(file, line);
        //std::cout << line << std::endl;

        std::unordered_map<std::string, std::array<int, 2> > nums
        {
            // key : (value, index)
            {"left_n", {-1, -1}},
            {"right_n", {-1, -1}},
            {"left_s", {-1, -1}},
            {"right_s", {-1, -1}},
        };

        std::unordered_map<std::string, int> lookup
        {
            // key : value
            {"one", 1},
            {"two", 2},
            {"three", 3},
            {"four", 4},
            {"five", 5},
            {"six", 6},
            {"seven", 7},
            {"eight", 8},
            {"nine", 9}
        };



        for (int i = 0; i < line.length(); i++)
        {
            char c = line[i];
            if (!isdigit(c))
            {
                continue;
            }
            if (nums["left_n"][0] == -1)
            {
                nums["left_n"] = { atoi(&c), i };
                nums["right_n"] = { atoi(&c), i };
            }
            else
            {
                nums["right_n"] = { atoi(&c), i };
            }
            
        }
        for (const auto& [key, value] : lookup)
        {
            //std::cout << key << ": " << value << ", ";
            std::size_t found = line.find(key);
            if (found != std::string::npos)
            {
               
                if (nums["left_s"][1] == -1) 
                {
                    nums["left_s"] = { value, int(found) };
                }
                else if (int(found) < nums["left_s"][1])
                {
                    nums["left_s"] = { value, int(found) };
                }
                
            }

        for (const auto& [key, value] : lookup)
        {
            std::size_t found = line.find(key, 0);
            std::vector<int> pos;
            while (found != std::string::npos)
            {
                pos.push_back(found);
                found = line.find(key, found + 1);
            }
            if (pos.size() > 0) 
            {
                std::size_t found = line.find(key, pos.back());
                if (nums["right_s"][1] == -1)
                {
                    nums["right_s"] = { value, int(found) };
                }
                else if (int(found) > nums["right_s"][1])
                {
                    nums["right_s"] = { value, int(found) };
                }
            }

        }

        }
        std::cout << line << std::endl;
        std::cout << k << std::endl;
            
        std::cout << "\tn:" << "left: (" << nums["left_n"][0] << ", " << nums["left_n"][1] << ")";
        std::cout << " right: (" << nums["right_n"][0] << ", " << nums["right_n"][1] << ")\n";

        std::cout << "\ts:" << "left: (" << nums["left_s"][0] << ", " << nums["left_s"][1] << ")";
        std::cout << " right: (" << nums["right_s"][0] << ", " << nums["right_s"][1] << ")\n";
        
        int left{ nums["left_n"][0] };
        int right{ nums["right_n"][0] };

        if (left == -1)
        {
            left = nums["left_s"][0];
        }
        else
        {
            if (nums["left_s"][1] < nums["left_n"][1] && nums["left_s"][1] != -1)
            {
                left = nums["left_s"][0];
            }
        }


        if (right == -1)
        {
            right = nums["right_s"][0];
        }
        else 
        {
            if (nums["right_s"][1] > nums["right_n"][1] && nums["right_n"][1] != -1)
            {
                right = nums["right_s"][0];
            }
        }


        std::cout << "\t" << "(" << left << ", " << right << ")\n";
        //sum += left * 10;
        //sum += right;
        if (left != -1 && right != -1)    //55276
        {
            sum += left * 10;
            sum += right;
        }
        std::cout << "\t" << sum << std::endl;

        k += 1;
    }

    file.close();
    std::cout << sum << std::endl;

    return 0;
}