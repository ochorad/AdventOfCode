#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>
#include <fstream>
#include <sstream>

// fuck it brute force for step 2

bool IsSafe(const std::vector<int>& array) {
    bool increasing = true;
    bool decreasing = true;
    
    for (int i = 1; i < array.size(); ++i) {
        int diff = abs(array[i] - array[i - 1]);
        if (diff < 1 || diff > 3) return false;
        if (array[i - 1] > array[i]) decreasing = false;
        if (array[i - 1] < array[i]) increasing = false;
    }
    return increasing || decreasing;
}

bool IsSafePart2(const std::vector<int>& array) {
    if (IsSafe(array)) return true;

    for (int i = 0; i < array.size(); ++i) {
        std::vector<int> modified;
        for (int j = 0; j < array.size(); ++j) { // cheeky skipper
            if (j != i) modified.push_back(array[j]);
        }
        if (IsSafe(modified)) return true;
    }

    return false;
}

void ReadDataFromFile(const std::string& filename, std::vector<std::vector<int>>& array_2d) {
    std::ifstream inputFile(filename);
    std::string line;
    int word;

     if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    while (getline(inputFile, line, '\n')) {
        std::vector<int> tmp_vec;
        std::istringstream ss(line);
        
        while(ss >> word) {
            tmp_vec.push_back(word);
        }
        array_2d.push_back(tmp_vec);
    }

    inputFile.close();
}


int main() {
    std::vector<std::vector<int>> array_2d;
    std::string file_name = "Day2-Data.txt";
    ReadDataFromFile(file_name, array_2d);
    int num_of_safe = 0;
    for (const auto& vec : array_2d) {
        // if (IsSafe(vec)) {
        //     num_of_safe++;
        // }
        if (IsSafePart2(vec)) {
            num_of_safe++;
        }
    }
    std::cout << "\n" << num_of_safe << "\n";

    return 0;
}