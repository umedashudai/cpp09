/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:32:19 by shuu              #+#    #+#             */
/*   Updated: 2026/03/01 15:49:16 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

    //1inputfileのバリテーションcheck
    //2inputfileとdatabaseのデータをcontaierに変換する
    //3inputfileにある日付ごとに為替変換する
    //標準出力

void BitcoinExchange::addInputData(char *filename) {
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

void BitcoinExchange::addDatabase() {
    std::fstream data;
    std::string line;
    std::vector<std::string> vec;
    
    data.open(CSV_DATA);
    if (!data.is_open())
        throw std::runtime_error("could not open csv data.");
    while (std::getline(data, line)) {
        if (line == FIRST_DATA_LINE)
            continue;
        std::istringstream iss(line);
        std::string str;
        while (std::getline(iss, str, ','))
            vec.push_back(str);
        _dataBase.insert(std::pair(vec[0], std::stod(vec[1])));
        vec.clear();
    }
}

void BitcoinExchange::processBitExchange(char *filename) {
    this->checkValidData();
    this->addInputData(filename);
    this->addDatabase();
}