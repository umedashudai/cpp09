/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:32:46 by shuu              #+#    #+#             */
/*   Updated: 2026/03/22 17:38:37 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#define FIRST_INPUT_LINE "date|value"
#define CSV_DATA "data.csv"
#define FIRST_DATA_LINE "date,exchange_rate"

class BitcoinExchange {
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        ~BitcoinExchange();
        BitcoinExchange& operator=(const BitcoinExchange& copy);
        static void printError(const std::string& error_message);
        static bool canOpenFiles(const char *arg_file);
        void addCSVToMap();
        void addInputToDeque(const char *file_name);
        void outputBitcoinExchange();
    private:
        bool checkVaildDate(const std::string& data_key);
        bool checkVaildExRate(const std::string& value, double& ex_num);
        std::map<std::string, double>::iterator findClosestDate(const std::string& data_key);
        void processInputEntry(const std::string& key, const std::string& value);
        std::map<std::string, double> _data_map;
        std::deque<std::pair<std::string, std::string> > _input_deq;
};

#endif
