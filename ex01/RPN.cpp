/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:01:19 by shuu              #+#    #+#             */
/*   Updated: 2026/03/22 18:59:39 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& copy) {
    if (this != &copy)
        *this = copy;
}

RPN& RPN::operator=(const RPN& copy) {
    (void)copy;
    return *this;
}

double RPN::add(double a, double b) {
    return a + b;
}

double RPN::sub(double a, double b) {
    return a - b;
}

double RPN::mlt(double a, double b) {
    return a * b;
}

double RPN::div(double a, double b) {
    if (b == 0)
        throw std::runtime_error("division by zero");
    return a / b;
}

void RPN::performOperation(const std::string &op, std::stack<double> &nums) {
  
  double a, b;
  std::map <std::string, double(*)(double, double)> operations;
  operations["+"] = &RPN::add;
  operations["-"] = &RPN::sub;
  operations["*"] = &RPN::mlt;
  operations["/"] = &RPN::div;

  if (nums.size() < 2)
    throw std::runtime_error("invalid stack size");
  b = nums.top();
  nums.pop();
  a = nums.top();
  nums.pop();

  if (operations.find(op) != operations.end())
    nums.push(operations[op](a, b));
}

bool RPN::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}
//逆ポーランド記法をstackを使って演算処理を行う時に、exprに演算子が現れるまでstackに代入する
double RPN::calc(const std::string& expr) {
    std::stack<double> nums;
    std::istringstream iss(expr);
    std::string token;
 
    while (iss >> token) {
        if (RPN::isOperator(token))
            RPN::performOperation(token, nums);
        else if (token.size() == 1 && std::isdigit(token[STR_INDEX]))
            nums.push(std::stod(token));
        else
            throw std::runtime_error("invalid token");
    }
    if (nums.size() != 1)
        throw std::runtime_error("invalid expression");
    return nums.top();
}
