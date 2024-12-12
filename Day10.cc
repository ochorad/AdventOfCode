#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

// Part 1: 00:24:55
// Part 2: 00:00:56

enum directions {
    left = 0,
    right,
    up,
    down,
    last
};

int TrailHeadFinder(std::vector<std::vector<int>>& array_2d, int vert, int horz, std::vector<std::pair<int, int>>& found_nines) {
    int num_of_trail_heads = 0;
    std::cout << "\nFound " << array_2d[vert][horz] << " at: vert:" << vert << " horz:" << horz << std::endl;
    for (int i = left; i != last; i++) {
        directions dir = static_cast<directions>(i);
        switch (dir) {
            case left : {
                if (horz-1 < 0) break;
                if (array_2d[vert][horz] == (array_2d[vert][horz-1] - 1) && (array_2d[vert][horz-1]) == 9) {
                    // bool found = false;
                    // for (auto pairs : found_nines) {
                    //     if (pairs.first == vert && pairs.second == horz-1) found = true;
                    // }
                    // if(!found) {
                    //     found_nines.push_back({vert,horz-1});
                        num_of_trail_heads++;
                    // } 
                    break;
                }
                if (array_2d[vert][horz] == (array_2d[vert][horz-1] - 1)) {
                    num_of_trail_heads += TrailHeadFinder(array_2d, vert, horz-1, found_nines);
                } 
                break;
            }
            case right : {
                if (horz+1 == array_2d[vert].size()) break;
                if (array_2d[vert][horz] == (array_2d[vert][horz+1] - 1) && (array_2d[vert][horz+1]) == 9) {
                    // bool found = false;
                    // for (auto pairs : found_nines) {
                    //     if (pairs.first == vert && pairs.second == horz+1) found = true;
                    // }
                    // if(!found) {
                    //     found_nines.push_back({vert,horz+1});
                        num_of_trail_heads++;
                    // } 
                    break;
                }
                if (array_2d[vert][horz] == (array_2d[vert][horz+1] - 1)) {
                    num_of_trail_heads += TrailHeadFinder(array_2d, vert, horz+1, found_nines);
                } 
                break;
            }
            case up : {
                if (vert+1 == array_2d.size()) break;
                if (array_2d[vert][horz] == (array_2d[vert+1][horz] - 1) && (array_2d[vert+1][horz]) == 9) {
                    // bool found = false;
                    // for (auto pairs : found_nines) {
                    //     if (pairs.first == vert+1 && pairs.second == horz) found = true;
                    // }
                    // if(!found) {
                    //     found_nines.push_back({vert+1,horz});
                        num_of_trail_heads++;
                    // } 
                    break;
                }
                if (array_2d[vert][horz] == (array_2d[vert+1][horz] - 1)) {
                    num_of_trail_heads += TrailHeadFinder(array_2d, vert+1, horz, found_nines);
                } 
                break;
            }
            case down : {
                if (vert-1 < 0) break;
                if (array_2d[vert][horz] == (array_2d[vert-1][horz] - 1) && (array_2d[vert-1][horz]) == 9) {
                    // bool found = false;
                    // for (auto pairs : found_nines) {
                    //     if (pairs.first == vert-1 && pairs.second == horz) found = true;
                    // }
                    // if(!found) {
                    //     found_nines.push_back({vert-1,horz});
                        num_of_trail_heads++;
                    // } 
                    break;
                }
                if (array_2d[vert][horz] == (array_2d[vert-1][horz] - 1)) {
                    num_of_trail_heads += TrailHeadFinder(array_2d, vert-1, horz, found_nines);
                } 
                break;
            }
            default: {
                std::cerr << "How did you end up here?" << dir;
                break;
            }
        }
    }
    return num_of_trail_heads;
}

int GetTrailheads(std::vector<std::vector<int>>& array_2d) {
    int total = 0;

    for (int vert = 0; vert < array_2d.size(); vert++) {
        for (int horz = 0; horz < array_2d[vert].size(); horz++) {
            std::vector<std::pair<int, int>> location_of_found_nines;
            if (array_2d[vert][horz] == 0) total += TrailHeadFinder(array_2d, vert, horz, location_of_found_nines);
        }
        std::cout << std::endl;
    }

    return total;
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
        for (char i : line) {
            tmp_vec.push_back((int)i - (int)'0');
        }
        array_2d.push_back(tmp_vec);
    }
    inputFile.close();
}

int main() {
    std::vector<std::vector<int>> array_2d;
    std::string file_name = "Day10-Data.txt";
    ReadDataFromFile(file_name, array_2d);
    int sum_of_trailheads = 0;
    sum_of_trailheads = GetTrailheads(array_2d);
    std::cout << "\n" << sum_of_trailheads << "\n";

    return 0;
}