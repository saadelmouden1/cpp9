#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>

class PmergeMe {
public:
    template <typename T>
    void merge_insertion_sort(T& container, int pair_level);

    template <typename T>
    static T next(T it, int steps);

    template <typename T>
    void _swap_pair(T it, int pair_level);
};

template <typename T>
T PmergeMe::next(T it, int steps)
{
    std::advance(it, steps);
    return it;
}


template <typename T> void PmergeMe::_swap_pair(T it, int pair_level)
{
    T start = next(it, -pair_level + 1);
    T end = next(start, pair_level);
    while (start != end)
    {
        std::iter_swap(start, next(start, pair_level));
        start++;
    }
}

template <typename T>
void PmergeMe::merge_insertion_sort(T& container, int pair_level)
{
    int element_nbr = container.size() / pair_level;
    if (element_nbr < 2)
        return;
    bool is_odd = element_nbr % 2 == 1;

    int end_index = element_nbr;
    if (is_odd)
        end_index -= 1; 

    for (int i = 0; i < end_index; i += 2)
    {
        typename T::iterator first_elem_start = next(container.begin(), i * pair_level);
        typename T::iterator first_elem_end   = next(first_elem_start, pair_level - 1);

        typename T::iterator second_elem_start = next(container.begin(), (i + 1) * pair_level);
        typename T::iterator second_elem_end   = next(second_elem_start, pair_level - 1);

        if (*second_elem_end < *first_elem_end)
            _swap_pair(first_elem_end, pair_level);
    }

    merge_insertion_sort(container, pair_level * 2);


     std::vector<typename T::iterator> main;
    std::vector<typename T::iterator> pend;

    main.push_back(next(container.begin(), pair_level - 1));
    main.push_back(next(container.begin(), pair_level * 2 - 1));

    
    for (int i = 4; i <= element_nbr; i += 2)
    {
        pend.push_back(next(container.begin(), pair_level * (i - 1) - 1));
        main.push_back(next(container.begin(), pair_level * i - 1));
    }

    if (is_odd)
    {
        pend.push_back(next(container.end(), -1));  // last leftover element
    }

    // // Print main chain
    // std::cout << "Main chain:" << std::endl;
    // for (size_t i = 0; i < main.size(); ++i)
    // {
    //     std::cout << *(main[i]) << " ";
    // }
    // std::cout << std::endl;

    // // Print pend chain
    // std::cout << "Pend chain:" << std::endl;
    // for (size_t i = 0; i < pend.size(); ++i)
    // {
    //     std::cout << *(pend[i]) << " ";
    // }
    // std::cout << std::endl;
}

#endif
