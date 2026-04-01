/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuu <shuu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:37:20 by shuu              #+#    #+#             */
/*   Updated: 2026/03/22 19:51:41 by shuu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _depth(0), _vec(), _lst(), _remainders() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::checkArgs(const int ac, char **sequence) {
    for (int i = 1; i < ac; i++) {
        for (size_t j = 0; sequence[i][j]; j++) {
            if (!std::isdigit(sequence[i][j]) && sequence[i][j] != ' ')
                throw std::logic_error("not correct argument");
        }
    }
}

void PmergeMe::setVectorAndList(const int ac, char **av) {
    for (int i = 1; i < ac; i++) {
        const char *arg =  av[i];
        char *end;
        long num = std::strtol(arg, &end, 10);
        if (*end != '\0' || num <= 0 || arg == end)
            throw std::invalid_argument("Invalid input: " + std::string(arg));
        if (num < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < num)
            throw std::out_of_range("out of range");
        p_vec vec_elem;
        p_lst lst_elem;
        vec_elem.num = num;
        _vec.push_back(vec_elem);
        lst_elem.num = num;
        _lst.push_back(lst_elem);
    }
}

long timeDiff(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

void PmergeMe::printVec(std::vector<p_vec>& vec) {
    for (size_t i = 0; i < vec.size()-1; i++) {
        std::cout << vec[i].num << " ";
    }
    std::cout << vec[vec.size()-1].num << std::endl;
}

//奇数の場合_remaindersにノードを追加する関数
void PmergeMe::vecFairing(std::vector<p_vec>& vec) {
    if (vec.size() % 2) {
        _remainders.pop_back();
        _remainders.push_back(vec.back());
        vec.pop_back();
    }
}

//木構造でmainchainとsubchainのペアを作る関数
void PmergeMe::makePair(std::vector<p_vec>& vec) {
    for (size_t i = 0; i < vec.size()-1; i++) {
        if (vec[i].num >= vec[i + 1].num) {
            vec[i].p_vecs.push_back(vec[i + 1]);
            vec.erase(vec.begin() + (i + 1));
        }
        else {
            vec[i + 1].p_vecs.push_back(vec[i]);
            vec.erase(vec.begin() + i);
        }
    }
}


std::vector<int> PmergeMe::createJacobsthalSequence(int n) {
    n *= 2;
    if (n == 0)
        return std::vector<int>();
    if (n == 1) {
        std::vector<int> result;
        result.push_back(1);
    }
    std::vector<int>    jacobthal;
    jacobthal.push_back(1);
    jacobthal.push_back(3);
    int next = 3;
    //ヤコブスタール数列の性質を利用して次のsubchainの要素の挿入境界indexを求めてjacobthalに代入する
    while (jacobthal.size() < static_cast<size_t>(n)) {
        next = jacobthal[jacobthal.size() - 1] + 2 * jacobthal[jacobthal.size() - 2];
        if (next > n)
            break;
        jacobthal.push_back(next);
    }
    std::vector<int>    result;
    result.push_back(1);
    //jacobthal境界indexから全ての挿入順を求めてresultに代入する。
    for (size_t i = 1; i < jacobthal.size(); i++) {
        for (int j = jacobthal[i]; j > jacobthal[i - 1]; j--) {
            if (j <= n)
                result.push_back(j);
        }
    }
    n /= 2;
    for (size_t i = 0; i < result.size(); i++) {
        if (n < result[i]) {
            result.erase(result.begin() + i);
            i--;
        }
    }
    return result;
}

size_t PmergeMe::binarySearchInsertPosition(std::vector<p_vec>& vec, p_vec value, size_t end) {
    size_t left = 0;
    size_t right = end;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (vec[mid].num < value.num)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void PmergeMe::insertSorted(std::vector<p_vec>& vec, p_vec value, size_t end) {
    try {
        if (end > vec.size())
            end = vec.size();
        size_t pos = binarySearchInsertPosition(vec, value, end);
        vec.insert(vec.begin() + pos, value);
    } catch(const std::exception& e) {
        std::cerr << "Error in insertSorted: " << e.what() << std::endl;
    }
}

std::vector<p_vec> PmergeMe::runMergeInsertionSort(std::vector<p_vec>& vec) {
    if (vec.size() < 2)
        return vec;
    _depth++;
    p_vec   remainder;
    /*remainderは階層ごとにその階層ではmainchainが偶数場合は−１を*/
    /*奇数の場合はvecFaring()でmainchainの最後の要素を_remaindersに追加する*/
    remainder.num = -1;
    _remainders.push_back(remainder);
    vecFairing(vec);
    makePair(vec);
    runMergeInsertionSort(vec);
    
    std::vector<int> jacobstal_order = createJacobsthalSequence(static_cast<int>(vec.size()));
    size_t pairsize = vec[0].p_vecs.size();
    if (pairsize >= 1) {
        vec.insert(vec.begin(), vec[0].p_vecs.back());
        vec[1].p_vecs.pop_back();
        for (size_t i = 1; i < jacobstal_order.size(); i++) {
            int pos = jacobstal_order[i] - 1;
            int count = 0;
            for (size_t j = 0; j < vec.size(); j++) {
                if (pairsize == vec[j].p_vecs.size())
                    count++;
                if (count == pos && vec[j].p_vecs.size() != 0) {
                    insertSorted(vec, vec[j].p_vecs.back(), j);
                    break;
                }
            }
        }
        for (size_t i = 0; i < vec.size(); i++) {
            if (pairsize == vec[i].p_vecs.size())
                vec[i].p_vecs.pop_back();
        }
    }
    if (_remainders[_depth - 1].num != -1) {
        insertSorted(vec, _remainders[_depth - 1], vec.size());
        _remainders.pop_back();
    }
    _depth--;
    return vec;
}



void PmergeMe::printList(std::list<p_lst>& lst) {
    for (std::list<p_lst>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << it->num << " ";
    std::cout << std::endl;
}

void PmergeMe::lstFairing(std::list<p_lst>& lst) {
    if (lst.size() % 2) {
        _remainder_list.pop_back();
        _remainder_list.push_back(lst.back());
        lst.pop_back();
    }
}

void PmergeMe::makePairList(std::list<p_lst>& lst) {
    for (size_t i = 1; i < lst.size(); i++) {
        std::list<p_lst>::iterator it_next = lst.begin();
        std::advance(it_next, i);
        std::list<p_lst>::iterator it_prev = lst.begin();
        std::advance(it_prev, i - 1);
        if (it_prev->num >= it_next->num) {
            it_prev->p_lsts.push_back(*it_next);
            lst.erase(it_next);
        }
        else {
            it_next->p_lsts.push_back(*it_prev);
            lst.erase(it_prev);
        }
    }
}

void PmergeMe::insertSortedList(std::list<p_lst>& lst, p_lst value, size_t end) {
    try {
        std::list<p_lst>::iterator it = lst.begin();
        for (size_t i = 0; i < end && it != lst.end(); i++)
            it = std::next(it);
        for (; it != lst.begin() && value < *std::prev(it); --it);
        lst.insert(it, value);
    } catch (const std::exception& e) {
        std::cerr << "Error in insertSortedList: " << e.what() << std::endl;
    }
}

std::list<p_lst> PmergeMe::runMergeInsertionSortList(std::list<p_lst>& lst) {
    if (lst.size() < 2)
        return lst;
    _depth++;
    p_lst remainder;
    remainder.num = -1;
    _remainder_list.push_back(remainder);
    lstFairing(lst);
    makePairList(lst);

    runMergeInsertionSortList(lst);

    std::vector<int> jacobstal_order = createJacobsthalSequence(static_cast<int>(lst.size()));
    int pairsize = lst.front().p_lsts.size();

    if (pairsize >= 1) {
        lst.push_front(lst.front().p_lsts.back());
        std::next(lst.begin(), 1)->p_lsts.pop_back();
        for (size_t i = 1; i < jacobstal_order.size(); i++) {
            int pos = jacobstal_order[i] - 1;
            int count = 0;
            for (size_t j = 0; j < lst.size(); j++) {
                std::list<p_lst>::iterator it = lst.begin();
                std::advance(it, j);
                if (pairsize == static_cast<int>(it->p_lsts.size()))
                    count++;
                if (count == pos && it->p_lsts.size() != 0) {
                    insertSortedList(lst, it->p_lsts.back(), j);
                    break;
                }
            }
        }
        for (size_t i = 0; i < lst.size(); i++) {
            std::list<p_lst>::iterator it = lst.begin();
            std::advance(it, i);
            if (pairsize == static_cast<int>(it->p_lsts.size()))
                it->p_lsts.pop_back();
        }
    }
    if (_remainder_list.size() > static_cast<size_t>(_depth - 1)) {
        if (std::next(_remainder_list.begin(), _depth - 1)->num != -1)
            insertSortedList(lst, *std::next(_remainder_list.begin(), _depth - 1), lst.size());
    }
    _depth--;
    return lst;
}

void PmergeMe::run() {
    struct timeval startVec, endVec, startList, endList;
    
    std::cout << "Before: ";
    printVec(_vec);
    gettimeofday(&startVec, NULL);
    std::vector<p_vec> resultVec = runMergeInsertionSort(_vec);
    gettimeofday(&endVec, NULL);
    gettimeofday(&startList, NULL);
    std::list<p_lst> resultList = runMergeInsertionSortList(_lst);
    gettimeofday(&endList, NULL);
    std::cout << "After: ";
    for (size_t i = 0; i < resultVec.size()-1; i++)
        std::cout << resultVec[i].num << " ";
    std::cout << resultVec[resultVec.size()-1].num << std::endl;
    #ifdef DEBUG
        std::cout << "Vector result:\n";
        printVec(resultVec);

        std::cout << "List result:\n";
        printList(resultList);
    #endif
    long durationVec = timeDiff(startVec, endVec);
    long durationList = timeDiff(startList, endList);
    std::cout << "Time to process a range of " << resultVec.size() << " elements with std::vector : " << durationVec << "us" << std::endl;
    std::cout << "Time to process a range of " << resultVec.size() << " elements with std::list : " << durationList << "us" << std::endl;
}
