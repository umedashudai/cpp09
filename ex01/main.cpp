/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:14:09 by shuu              #+#    #+#             */
/*   Updated: 2026/03/22 18:49:21 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <mathematical expression>"  << std::endl;
        return 1;
    }
    try {
        std::cout << RPN::calc(av[1]) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: "<< e.what() << std::endl;
    }
    return 0;
}
