/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 17:32:00 by shuu              #+#    #+#             */
/*   Updated: 2026/03/22 16:48:44 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int ac, char **av) {
    BitcoinExchange btc;

    if (ac != 2) {
        std::cout << "Usage: " << av[0] << " <input file>" << std::endl;
        return 1;
    }
    if (!BitcoinExchange::canOpenFiles(av[1]))
        return 1;
    BitcoinExchange btcExchange;
	btcExchange.addCSVToMap();
	btcExchange.addInputToDeque(av[1]);
	btcExchange.outputBitcoinExchange();
   return 0;
}
