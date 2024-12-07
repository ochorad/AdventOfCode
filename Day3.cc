#include <iostream>
#include <ostream>
#include <string> 
#include <fstream>
#include <sstream>
#include <regex>

// Step 1: 00:47:34
// Step 2: 00:04:35 HOLY SHITTTTT!!!!

int LoopThruString(std::string& data) {
    int total = 0;
    std::regex mul_regex(R"(mul\([0-9]{1,3},[0-9]{1,3}\)|do\(\)|don't\(\))");
    auto mul_regex_iter_begin = std::sregex_iterator(data.begin(), data.end(), mul_regex);
    auto mul_regex_iter_end = std::sregex_iterator();
    std::regex num_regex(R"(\b[0-9]{1,3}\b)");
    bool _do_ = true;
    for (std::sregex_iterator i = mul_regex_iter_begin; i != mul_regex_iter_end; i++) {
        std::smatch match = *i;
        std::string s_match = match.str();
        if (s_match == "do()") _do_ = true;
        if (s_match == "don't()") _do_ = false;
        auto num_regex_iter_begin = std::sregex_iterator(s_match.begin(), s_match.end(), num_regex);
        auto num_regex_iter_end = std::sregex_iterator();
        std::vector<int> two_num;
        for (std::sregex_iterator j = num_regex_iter_begin; j != num_regex_iter_end; j++) {
            std::smatch num = *j;
            std::string num_s_match = num.str();
            two_num.push_back(std::stoi(num_s_match)); 
        }
        if (two_num.size() == 2 && _do_) total += two_num[0]*two_num[1]; // I know its dangerous, chill
    }
    return total;
}

std::string ReadDataFromFile(const std::string& file_name) {
    std::ifstream file(file_name);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    std::string data = ReadDataFromFile("Day3-Data.txt");
    std::cout << LoopThruString(data) << std::endl;
    return 0;
}