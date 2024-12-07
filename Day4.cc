#include <iterator>
#include <ostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

// Part 1 : 01:13:47 I dont want to talk about it...
// Part 2 : 00:17:11 Not shabby 


enum directions {
    UP = 0,
    UP_RIGHT = 1,
    RIGHT = 2,
    DOWN_RIGHT = 3,
    DOWN = 4,
    DOWN_LEFT = 5,
    LEFT = 6,
    UP_LEFT = 7,
    END = 8
};

enum double_m {
    TOP = 1,
    FRONT = 2,
    BOTTOM = 3,
    BACK = 4,
    END_M = 5
};

bool IsWord(std::vector<std::vector<std::string>>& array_2d, int vert_index, int horz_index, int vert_val, int horz_val) {
    if (array_2d[vert_index + vert_val][horz_index + horz_val] != "M") return false;
    if (array_2d[vert_index + (vert_val * 2)][horz_index + (horz_val * 2)] != "A") return false;
    if (array_2d[vert_index + (vert_val * 3)][horz_index + (horz_val * 3)] != "S") return false;
    return true;
}

bool IsWord2(std::vector<std::vector<std::string>>& array_2d, int vert_index, int horz_index, int vert_val, int horz_val) {
    bool check_left_right = false;
    bool check_up_down = false;
    if (vert_val == 1 || vert_val == -1) check_left_right = true;
    if (horz_val == 1 || horz_val == -1) check_up_down = true;
    
    if (check_left_right) {
        if (array_2d[vert_index + vert_val][horz_index + 1] != "M") return false;
        if (array_2d[vert_index + vert_val][horz_index - 1] != "M") return false;
        if (array_2d[vert_index - vert_val][horz_index + 1] != "S") return false;
        if (array_2d[vert_index - vert_val][horz_index - 1] != "S") return false;
    }

    if (check_up_down) {
        if (array_2d[vert_index + 1][horz_index + horz_val] != "M") return false;
        if (array_2d[vert_index - 1][horz_index + horz_val] != "M") return false;
        if (array_2d[vert_index + 1][horz_index - horz_val] != "S") return false;
        if (array_2d[vert_index - 1][horz_index - horz_val] != "S") return false;
    }

    return true;
}

bool IsValidIndex(int vert_index, int horz_index, int vert_val, int horz_val, int horz_size, int vert_size) { // vert and horz val : UP=1 DOWN=-1 | LEFT=-1 RIGHT=1 | No Change = 0
    if (vert_index + (vert_val*3) < 0 || vert_index + (vert_val*3) >= vert_size) return false;
    if (horz_index + (horz_val*3) < 0 || horz_index + (horz_val*3) >= horz_size) return false;
    return true;
}

bool IsValidIndex2(int vert_index, int horz_index, int horz_size, int vert_size) { // vert and horz val : UP=1 DOWN=-1 | LEFT=-1 RIGHT=1 | No Change = 0
    if (vert_index - 1 < 0 || vert_index + 1 >= vert_size) return false;
    if (horz_index - 1 < 0 || horz_index + 1 >= horz_size) return false;
    return true;
}

int CheckForXMAS(std::vector<std::vector<std::string>>& array_2d, int vert_index, int horz_index) {
    int num_of_XMAS_words = 0;
    for (int i = UP; i < END; ++i) {
        switch (static_cast<directions>(i)) {
            case UP : { // VERT=1 HORZ=0
                if (IsValidIndex(vert_index, horz_index, 1, 0, array_2d.size(), array_2d[0].size())) {
                    if (IsWord(array_2d, vert_index, horz_index, 1, 0)) num_of_XMAS_words++;
                }
                break;
            }
            case UP_RIGHT : { // VERT=1 HORZ=1
                if (IsValidIndex(vert_index, horz_index, 1, 1, array_2d.size(), array_2d[0].size())) {
                    if (IsWord(array_2d, vert_index, horz_index, 1, 1)) num_of_XMAS_words++;
                }
                break;
            }
            case RIGHT : { // VERT=0 HORZ=1
                if (IsValidIndex(vert_index, horz_index, 0, 1, array_2d.size(), array_2d[0].size())) {
                    if (IsWord(array_2d, vert_index, horz_index, 0, 1)) num_of_XMAS_words++;
                }
                break;
            }
            case DOWN_RIGHT : { // VERT=-1 HORZ=1
                if (IsValidIndex(vert_index, horz_index, -1, 1, array_2d.size(), array_2d[0].size())) {
                    if (IsWord(array_2d, vert_index, horz_index, -1, 1)) num_of_XMAS_words++;
                }
                break;
            }
            case DOWN : { // VERT=-1 HORZ=0
                if (IsValidIndex(vert_index, horz_index, -1, 0, array_2d.size(), array_2d[0].size())) {
                    if (IsWord(array_2d, vert_index, horz_index, -1, 0)) num_of_XMAS_words++;
                }
                break;
            }
            case DOWN_LEFT : { // VERT=-1 HORZ=-1
                if (IsValidIndex(vert_index, horz_index, -1, -1, array_2d.size(), array_2d[0].size())) {
                    if (IsWord(array_2d, vert_index, horz_index, -1, -1)) num_of_XMAS_words++;
                }
                break;
            }
            case LEFT : { // VERT=0 HORZ=-1
                if (IsValidIndex(vert_index, horz_index, 0, -1, array_2d.size(), array_2d[0].size())) {
                    if (IsWord(array_2d, vert_index, horz_index, 0, -1)) num_of_XMAS_words++;
                }
                break;
            }
            case UP_LEFT : { // VERT=1 HORZ=-1
                if (IsValidIndex(vert_index, horz_index, 1, -1, array_2d.size(), array_2d[0].size())) {
                    if (IsWord(array_2d, vert_index, horz_index, 1, -1)) num_of_XMAS_words++;
                }
                break;
            }
            default : std::cerr << "\nHow did I end up here?" << i << ""; break;
        }
    }
    return num_of_XMAS_words;
}

int CheckFor2MAS(std::vector<std::vector<std::string>>& array_2d, int vert_index, int horz_index) {
    int num_of_XMAS_words = 0;
    for (int i = TOP; i < END_M; ++i) {
        switch (static_cast<double_m>(i)) {
            case TOP : { // VERT=1 HORZ=0
                if (IsValidIndex2(vert_index, horz_index, array_2d.size(), array_2d[0].size())) {
                    if (IsWord2(array_2d, vert_index, horz_index, 1, 0)) num_of_XMAS_words++;
                }
                break;
            }
            case FRONT : { // VERT=0 HORZ=1
                if (IsValidIndex2(vert_index, horz_index, array_2d.size(), array_2d[0].size())) {
                    if (IsWord2(array_2d, vert_index, horz_index, 0, 1)) num_of_XMAS_words++;
                }
                break;
            }
            case BOTTOM : { // VERT=-1 HORZ=0
                if (IsValidIndex2(vert_index, horz_index, array_2d.size(), array_2d[0].size())) {
                    if (IsWord2(array_2d, vert_index, horz_index, -1, 0)) num_of_XMAS_words++;
                }
                break;
            }
            case BACK : { // VERT=0 HORZ=-1
                if (IsValidIndex2(vert_index, horz_index, array_2d.size(), array_2d[0].size())) {
                    if (IsWord2(array_2d, vert_index, horz_index, 0, -1)) num_of_XMAS_words++;
                }
                break;
            }
            default : std::cerr << "\nHow did I end up here?" << i << ""; break;
        }
    }
    return num_of_XMAS_words;
}

int LoopThruLetters(std::vector<std::vector<std::string>>& array_2d) {
    int num_of_xmas = 0;
    int vert_index = 0;
    for (auto vert : array_2d) {
        int horz_index = 0;
        for (auto horz : vert) {
            if (horz == "X") num_of_xmas += CheckForXMAS(array_2d, vert_index, horz_index);
            horz_index++;
        }
        vert_index++;
    }
    return num_of_xmas;
}

int LoopThruLetters2(std::vector<std::vector<std::string>>& array_2d) {
    int num_of_xmas = 0;
    int vert_index = 0;
    for (auto vert : array_2d) {
        int horz_index = 0;
        for (auto horz : vert) {
            if (horz == "A") num_of_xmas += CheckFor2MAS(array_2d, vert_index, horz_index);
            horz_index++;
        }
        vert_index++;
    }
    return num_of_xmas;
}

void ReadDataFromFile(const std::string& filename, std::vector<std::vector<std::string>>& array_2d) { // 2D array
    std::ifstream inputFile(filename);
    std::string line;

     if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int vert_index = 0;
    while (getline(inputFile, line, '\n')) {
        int horz_index = 0;
        std::vector<std::string> temp;
        array_2d.push_back(temp);
        for (auto letter : line) {
            std::string tmp_str(1, letter);
            array_2d[vert_index].push_back(tmp_str);
            horz_index++;
        }
        vert_index++;
    }

    inputFile.close();
}

int main() {
    std::vector<std::vector<std::string>> array_2d;
    ReadDataFromFile("Day4-Data.txt", array_2d);
    std::cout << LoopThruLetters(array_2d) << std::endl;
    std::cout << LoopThruLetters2(array_2d) << std::endl;

    return 0;
}