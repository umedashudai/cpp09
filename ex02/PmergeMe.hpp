/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:37:42 by shuu              #+#    #+#             */
/*   Updated: 2026/03/22 19:53:00 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME
# define PMERGEME

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <sys/time.h>

typedef struct s_vec {
    long num;
    std::vector<s_vec> p_vecs;
    bool operator<(const s_vec other) const {
        return num < other.num;
    }
} p_vec;

typedef struct s_lst {
    long num;
    std::list<s_lst> p_lsts;
    bool operator<(const s_lst other) const {
        return num < other.num;
    }
} p_lst;

class PmergeMe {
    public:
        PmergeMe();
        ~PmergeMe();
        void checkArgs(const int ac, char **sequence);
        void run();
        std::vector<p_vec> runMergeInsertionSort(std::vector<p_vec>& vec);
        std::list<p_lst> runMergeInsertionSortList(std::list<p_lst>& lst);
        std::vector<int> createJacobsthalSequence(int n);
        void insertSorted(std::vector<p_vec>& vec, p_vec value, size_t end);
        void insertSortedList(std::list<p_lst>& lst, p_lst value, size_t end);
        size_t binarySearchInsertPosition(std::vector<p_vec>& vec, p_vec value, size_t end);
        void vecFairing(std::vector<p_vec>& vec);
        void lstFairing(std::list<p_lst>& lst);
        void makePair(std::vector<p_vec>& vec);
        void makePairList(std::list<p_lst>& lst);
        void setVectorAndList(const int ac, char **av);
        void printVec(std::vector<p_vec>& vec);
        void printList(std::list<p_lst>& lst);
    private:
        int _depth; //階層
        std::vector<p_vec>  _vec;
        std::list<p_lst> _lst;
        std::vector<p_vec> _remainders; //奇数の要素
        std::list<p_lst> _remainder_list;
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& copy);
};

#endif
