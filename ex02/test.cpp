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

std::vector<p_vec> setVectorAndList(const int ac, char **av) {
    std::vector<p_vec> vec;
    for (int i = 1; i < ac; i++) {
        const char *arg =  av[i];
        char *end;
        long num = std::strtol(arg, &end, 10);
        if (*end != '\0' || num <= 0 || arg == end)
            throw std::invalid_argument("Invalid input: " + std::string(arg));
        if (num < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < num)
            throw std::out_of_range("out of range");
        p_vec vec_elem;
        vec_elem.num = num;
        vec.push_back(vec_elem);
    }
    return vec;
}

void makePair(std::vector<p_vec>& vec) {
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

int main(int ac, char **av) {

    std::vector<p_vec> vec = setVectorAndList(ac, av);
    makePair(vec);
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i].num << ":" << vec[i].p_vecs[0].num << std::endl;
    }
    return 0;
}