
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
    
    std::fstream input;
    std::string line;

    input.open(filename);
    if (!input.is_open())
        throw std::runtime_error("could not open input file.");
    while (std::getline(input, line)) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        if (line == FIRST_INPUT_LINE)
            continue;
        if (std::string::npos != line.find("|")) {
            std::string lvalue = line.substr(0, 10);
            std::string rvalue = line.substr(11);
            _inputData.push_back(std::pair<std::string, double>(lvalue, std::stod(rvalue)));
        }
        else
            throw std::runtime_error("invaild input data");
    }
}
