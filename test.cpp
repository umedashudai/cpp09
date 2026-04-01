
#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#define FIRST_INPUT_LINE "date|value"
#define CSV_DATA "data.csv"
#define FIRST_DATA_LINE "date,exchange_rate"

int main() {
    
//     std::fstream input;
//     std::string line;
//     std::vector <std::pair<std::string,double> >_inputData;

//     input.open("input copy.txt");
//     if (!input.is_open())
//         throw std::runtime_error("could not open input file.");
//     while (std::getline(input, line)) {
//         line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
//         line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
//         if (line == FIRST_INPUT_LINE)
//             continue;
//         if (std::string::npos != line.find("|")) {
//             std::string lvalue = line.substr(0, 10);
//             std::string rvalue = line.substr(11);
//             _inputData.push_back(std::pair<std::string, double>(lvalue, std::stod(rvalue)));
//         }
//         else
//             throw std::runtime_error("invaild input data");
//     }
//     for (size_t i = 0; i < _inputData.size(); i++) {
//         std::cout << _inputData[i].first << " " << _inputData[i].second << std::endl;
//     }
    std::vector<int> vec;
    int a = 3;
    int& b = a;
    vec.push_back(1);
    vec.push_back(2);
    vec.insert(vec.begin() + 1, b);
    std::cout << vec[1] << std::endl;
}
