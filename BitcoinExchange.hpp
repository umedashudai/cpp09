/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:32:46 by shuu              #+#    #+#             */
/*   Updated: 2026/03/01 14:44:21 by shuu             ###   ########.fr       */
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
        void processBitExchange(char *filename);
        void addInputData(char *filename);
        void addDatabase();
    private:
        void checkValidData();
        std::deque<std::pair<std::string, double> >_inputData;
        std::map<std::string, double> _dataBase;
};

#endif