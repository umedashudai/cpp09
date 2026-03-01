/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 17:32:00 by shuu              #+#    #+#             */
/*   Updated: 2026/03/01 14:11:36 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int ac, char **av) {
    BitcoinExchange btc;

    if (ac != 2)
        std::cerr << "Error: could not open file" << std::endl;
    try {
        btc.processBitExchange(av[1]);
    }
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; 
    }
   return 0;
}