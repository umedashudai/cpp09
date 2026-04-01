/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:32:54 by shuu              #+#    #+#             */
/*   Updated: 2026/03/22 18:55:04 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <map>
#include <stack>
#include <iostream>
#include <sstream>
#define STR_INDEX 0

class RPN {
    public:
        RPN();
        ~RPN();
        static double calc(const std::string& expr);
        static void performOperation(const std::string &op, std::stack<double> &nums);
        static bool isOperator(const std::string& token);
        static double add(double a, double b);
        static double sub(double a, double b);
        static double mlt(double a, double b);
        static double div(double a, double b);
    private:
        RPN(const RPN& copy);
        RPN& operator=(const RPN& copy);
};

#endif
