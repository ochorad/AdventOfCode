#include <cstdio>
#include <fstream>
#include <iterator>
#include <map>
#include <ostream>
#include <set>
#include <utility>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <string>

// Part 1: 01:36:29
// Part 2: 01:00:59

void ParseRulePushBack(std::vector<std::pair<int,int>>& rules, const std::string& line) {
    std::regex pair_parser(R"(\d{2})");
    auto line_begin = std::sregex_iterator(line.begin(), line.end(), pair_parser);
    auto line_end = std::sregex_iterator();
    std::pair<int, int> tmp_pair;
    int iter = 0;
    for (auto i = line_begin; i != line_end; i++) {
        auto smatch = *i;
        if (iter == 0) tmp_pair.first = std::stoi(smatch.str());
        else if (iter == 1) tmp_pair.second = std::stoi(smatch.str());
        iter++;
    }
    std::cout << "Adding " << tmp_pair.first << "," << tmp_pair.second << " to Rules" << std::endl;

    rules.push_back(tmp_pair);
}


void ParseUpdatePushBack(std::vector<std::vector<int>>& updates, const std::string& line) {
    std::regex update_parser(R"(\d{2})");
    auto line_begin = std::sregex_iterator(line.begin(), line.end(), update_parser);
    auto line_end = std::sregex_iterator();
    std::vector<int> tmp_vec;
    std::cout << "Adding ";
    for (auto i = line_begin; i != line_end; i++) {
        auto smatch = *i;
        tmp_vec.push_back(std::stoi(smatch.str()));
        std::cout << std::stoi(smatch.str()) << " ";
    }
    std::cout << " to Updates" << std::endl;
    updates.push_back(tmp_vec);
}

void ReadDataFromFile(const std::string& filename, std::vector<std::pair<int,int>>& rules, std::vector<std::vector<int>>& updates) {
    std::ifstream inputFile(filename);
    std::string line;
    bool past_rules = false;
    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    while (getline(inputFile, line, '\n')) {
        std::pair<int,int> tmp_pair;
        std::istringstream ss(line);
        std::string line = ss.str();
        std::cout << line << std::endl;
        if (line.size() < 2) past_rules = true;
        else if (past_rules) ParseUpdatePushBack(updates, line);
        else ParseRulePushBack(rules, line);
    }

    inputFile.close();
}

void ParseRules(std::vector<std::pair<int,int>>& rules, std::map<int, std::set<int>>& efficient_rules) {
    for (auto rule : rules) {
        auto iter = efficient_rules.find(rule.first);
        if (iter != efficient_rules.end()) iter->second.emplace(rule.second);
        else {
            std::set<int> tmp_set = {rule.second};
            efficient_rules.emplace(rule.first, tmp_set);
        };
    }
    
    std::cout << "CHECKING IF PARSED RIGHT" << std::endl;
    for (auto rule_line : efficient_rules) {
        std::cout << rule_line.first << ": ";
        for (auto rule : rule_line.second) {
            std::cout << rule << " ";
        }
        std::cout << std::endl;
    }
}

bool IsValidUpdate(std::vector<int>& update, std::map<int, std::set<int>>& efficient_rules) {
    for (auto num : update) {
        bool after = false;
        for (auto num_nested : update) { // to check every number before
            if (after && efficient_rules.find(num_nested) != efficient_rules.end()) {
                for (auto set_iter : efficient_rules.at(num_nested)) {
                    if (num == set_iter)  {
                      return false;  
                    } 
                }
            }
            if (num_nested == num) after = true;
        }
    }
    return true;
}

int CheckValidUpdates(std::vector<std::vector<int>>& updates, std::map<int, std::set<int>>& efficient_rules, std::vector<std::vector<int>>& broken_updates) {
    int middle_page_sum = 0;
    int index = 0;
    for (auto update : updates) {
        if (IsValidUpdate(update, efficient_rules)) {
            middle_page_sum += update[(update.size()/2)];
        }
        else { // for part 2
            broken_updates.push_back(update);
        }
        index++;
    }
    return middle_page_sum;
}

void FixBrokenUpdates(std::map<int, std::set<int>>& efficient_rules, std::vector<std::vector<int>>& broken_updates) {
    std::vector<std::vector<int>> fixed_updates;
    int iter = 0;
    for (auto update : broken_updates) {
        std::vector<int> tmp_vector = {};
        std::cout << iter << " :\n";
        for (auto num : update) {
            std::cout << num << " ";
            if (tmp_vector.size() == 0)  {
                tmp_vector.push_back(num);
                continue;
            }
            int insert_in_index = -1;
            for (int i = 0; i < tmp_vector.size(); i++) {
                if (efficient_rules.find(tmp_vector[i]) == efficient_rules.end()) insert_in_index = i;
                else if (efficient_rules.at(tmp_vector[i]).find(num) != efficient_rules.at(tmp_vector[i]).end()) continue;
                else insert_in_index = i;
                break;
            }
            if (insert_in_index == -1) tmp_vector.push_back(num);
            else tmp_vector.insert(tmp_vector.begin()+insert_in_index, num);
        }
        std::cout << "\nFixed line: ";
        for (auto num : tmp_vector) {
            std::cout << num << ", ";
        }
        fixed_updates.push_back(tmp_vector);
        iter++;
    }
    broken_updates = fixed_updates;
}


int main() {
    int middle_page_sum = 0;
    int middle_page_sum_broken = 0;
    std::vector<std::pair<int,int>> rules;
    std::vector<std::vector<int>> updates;
    std::vector<std::vector<int>> broken_updates; // for part 2
    ReadDataFromFile("Day5-Data.txt", rules, updates);
    std::map<int, std::set<int>> efficient_rules;
    ParseRules(rules, efficient_rules);
    std::cout << "\n\n------------------------------------------\n\n";
    middle_page_sum = CheckValidUpdates(updates, efficient_rules, broken_updates);
    std::cout << middle_page_sum << std::endl; // for part 1
    FixBrokenUpdates(efficient_rules, broken_updates);
    std::vector<std::vector<int>> empty;
    middle_page_sum_broken = CheckValidUpdates(broken_updates, efficient_rules, empty);
    std::cout << std::endl << middle_page_sum_broken << std::endl; // for part 2


    return 0;
}