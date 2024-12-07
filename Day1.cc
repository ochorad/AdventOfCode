#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

int DifferenceBetween(int left, int right) {
    return (abs(left-right));
}

int NumberOfLeftValuesInRightVector(int left_val, std::vector<int>& rightVector) {
    // Horribly inefficient I think 
    int total = 0;
    for (auto iter : rightVector) {
        if (left_val == iter) {
            total++;
        }
        else if (left_val < iter) { // since vector is sorted, stop once the value has passed the number we need
            break;
        }
    }
    return total;
}

void ReadDataFromFile(const std::string& filename, std::vector<int>& leftVector, std::vector<int>& rightVector) {
    std::ifstream inputFile(filename);

     if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int left, right;
    while (inputFile >> left >> right) {
        leftVector.push_back(left);
        rightVector.push_back(right);
    }

    inputFile.close();
}


int main() {
    std::string file_name = "Day1-Data.txt";
    std::vector<int> left;
    std::vector<int> right;
    ReadDataFromFile(file_name, left, right);
    int total_difference = 0;
    int total_similarity = 0;
    std::stable_sort(right.begin(), right.end());
    std::stable_sort(left.begin(), left.end());

    for(int i = 0; i < left.size(); i++) {
        total_difference += (DifferenceBetween(left[i], right[i]));
        total_similarity += (left[i] * NumberOfLeftValuesInRightVector(left[i], right));
    }

    std::cout << "\n" << total_difference << "\n" << total_similarity << "\n";

    return 0;
}