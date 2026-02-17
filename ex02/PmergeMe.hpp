#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cmath>

class PmergeMe {
public:
    template <typename T>
    void merge_insertion_sort(T& container, int pair_level);

    template <typename T>
    static T next(T it, int steps);

    template <typename T>
    void _swap_pair(T it, int pair_level);

    static int nbr_of_comps;


    long _jacobsthal_number(long n);
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



long PmergeMe::_jacobsthal_number(long n) { return round((pow(2, n + 1) + pow(-1, n)) / 3); }


int PmergeMe::nbr_of_comps = 0;
template <typename T> bool _comp(T lv, T rv) {
	PmergeMe::nbr_of_comps++;
	return *lv < *rv;
}
// template <typename T>
// void PmergeMe::merge_insertion_sort(T& container, int pair_level)
// {
//        typedef typename T::iterator Iterator;

//     int element_nbr = container.size() / pair_level;
//     if (element_nbr < 2)
//         return;
//     bool is_odd = element_nbr % 2 == 1;

//     int end_index = element_nbr;
//     if (is_odd)
//         end_index -= 1; 

//     for (int i = 0; i < end_index; i += 2)
//     {
//         typename T::iterator first_elem_start = next(container.begin(), i * pair_level);
//         typename T::iterator first_elem_end   = next(first_elem_start, pair_level - 1);

//         typename T::iterator second_elem_start = next(container.begin(), (i + 1) * pair_level);
//         typename T::iterator second_elem_end   = next(second_elem_start, pair_level - 1);

//         if (*second_elem_end < *first_elem_end)
//             _swap_pair(first_elem_end, pair_level);
//     }

//     merge_insertion_sort(container, pair_level * 2);


//      std::vector<Iterator> main;
//     std::vector<Iterator> pend;

//     main.push_back(next(container.begin(), pair_level - 1));
//     main.push_back(next(container.begin(), pair_level * 2 - 1));

    
//     for (int i = 4; i <= element_nbr; i += 2)
//     {
//         pend.push_back(next(container.begin(), pair_level * (i - 1) - 1));
//         main.push_back(next(container.begin(), pair_level * i - 1));
//     }

//     if (is_odd)
//     {
//         pend.push_back(next(container.end(), -1));  // last leftover element
//     }
// std::cout << "Recursion level (pair_level = " << pair_level << "):\n";
// std::cout << "Main: ";
// for (typename std::vector<Iterator>::iterator it = main.begin(); it != main.end(); ++it)
//     std::cout << *(*it) << " ";
// std::cout << "\nPend: ";
// for (typename std::vector<Iterator>::iterator it = pend.begin(); it != pend.end(); ++it)
//     std::cout << *(*it) << " ";
// std::cout << "\n\n";
//        int prev_jacobsthal = _jacobsthal_number(1);
//     int inserted_numbers = 0;
//     for (int k = 2;; k++)
//     {
//         int curr_jacobsthal = _jacobsthal_number(k);
//         int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
// 		int offset = 0;
//         if (jacobsthal_diff > static_cast<int>(pend.size()))
//             break;
//         int nbr_of_times = jacobsthal_diff;
//         typename std::vector<Iterator>::iterator pend_it = next(pend.begin(), jacobsthal_diff - 1);
//         typename std::vector<Iterator>::iterator bound_it =
//             next(main.begin(), curr_jacobsthal + inserted_numbers);
//         while (nbr_of_times)
//         {
//             typename std::vector<Iterator>::iterator idx =
//                 std::upper_bound(main.begin(), bound_it, *pend_it, _comp<Iterator>);
//             typename std::vector<Iterator>::iterator inserted = main.insert(idx, *pend_it);
//             nbr_of_times--;
//             pend_it = pend.erase(pend_it);
//             std::advance(pend_it, -1);
//             /* Sometimes the inserted number in inserted at the exact index of where the bound should be.
// 			   When this happens, it eclipses the bound of the next pend, and it does more comparisons
// 			   than it should. We need to offset when this happens. */
//             offset += (inserted - main.begin()) == curr_jacobsthal + inserted_numbers;
// 			bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers - offset);
//         }
//         prev_jacobsthal = curr_jacobsthal;
//         inserted_numbers += jacobsthal_diff;
// 		offset = 0;
//     }

//     /* Insert the remaining elements in the reversed order. Here we also want to
//        perform as less comparisons as possible, so we calculate the starting bound
//        to insert pend number to be the pair of the first pend number. If the first
//        pend number is b8, the bound is a8, if the pend number is b7, the bound is a7 etc.
//        With the way I do it the index of bound is
//        size_of_main - size_of_pend + index_of_current_pend. */
//     for (ssize_t i = pend.size() - 1; i >= 0; i--)
//     {
//         typename std::vector<Iterator>::iterator curr_pend = next(pend.begin(), i);
//         typename std::vector<Iterator>::iterator curr_bound =
//             next(main.begin(), main.size() - pend.size() + i + is_odd);
//         typename std::vector<Iterator>::iterator idx =
//             std::upper_bound(main.begin(), curr_bound, *curr_pend, _comp<Iterator>);
//         main.insert(idx, *curr_pend);
//     }

// }








template <typename T>
void PmergeMe::merge_insertion_sort(T& container, int pair_level)
{
    typedef typename T::iterator Iterator;

    int element_nbr = container.size() / pair_level;
    if (element_nbr < 2)
        return;

    bool is_odd = element_nbr % 2 == 1;

    // Correct end for swapping (ignore odd block)
    Iterator start = container.begin();
    Iterator last  = next(container.begin(), pair_level * element_nbr);
    Iterator end   = next(last, -(is_odd * pair_level));

    // 1) Swap adjacent blocks
    int jump = 2 * pair_level;
    for (Iterator it = start; it != end; std::advance(it, jump))
    {
        Iterator first_elem_end  = next(it, pair_level - 1);
        Iterator second_elem_end = next(it, pair_level * 2 - 1);
        if (*second_elem_end < *first_elem_end)
            _swap_pair(first_elem_end, pair_level);
    }

    // 2) Recurse with doubled pair level
    merge_insertion_sort(container, pair_level * 2);

    // 3) Build main and pend chains
    std::vector<Iterator> main;
    std::vector<Iterator> pend;

    main.push_back(next(container.begin(), pair_level - 1));        // b1
    main.push_back(next(container.begin(), pair_level * 2 - 1));    // a1

    for (int i = 4; i <= element_nbr; i += 2)
    {
        pend.push_back(next(container.begin(), pair_level * (i - 1) - 1));  // bi
        main.push_back(next(container.begin(), pair_level * i - 1));        // ai
    }

    if (is_odd)
        pend.push_back(next(end, pair_level - 1));  // leftover block


//     std::cout << "Recursion level (pair_level = " << pair_level << "):\n";
// std::cout << "Main: ";
// for (typename std::vector<Iterator>::iterator it = main.begin(); it != main.end(); ++it)
//     std::cout << *(*it) << " ";
// std::cout << "\nPend: ";
// for (typename std::vector<Iterator>::iterator it = pend.begin(); it != pend.end(); ++it)
//     std::cout << *(*it) << " ";
// std::cout << "\n\n";
    // 4) Insert pend using Jacobsthal order
    int prev_jacobsthal = _jacobsthal_number(1);
    int inserted_numbers = 0;

    for (int k = 2;; k++)
    {
        int curr_jacobsthal = _jacobsthal_number(k);
        int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
        int offset = 0;

        if (jacobsthal_diff > static_cast<int>(pend.size()))
            break;

        int nbr_of_times = jacobsthal_diff;
        typename std::vector<Iterator>::iterator pend_it = next(pend.begin(), jacobsthal_diff - 1);
        typename std::vector<Iterator>::iterator bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers);

        while (nbr_of_times)
        {
            typename std::vector<Iterator>::iterator idx =
                std::upper_bound(main.begin(), bound_it, *pend_it, _comp<Iterator>);
            typename std::vector<Iterator>::iterator inserted = main.insert(idx, *pend_it);
            nbr_of_times--;
            pend_it = pend.erase(pend_it);
            std::advance(pend_it, -1);
            offset += (inserted - main.begin()) == curr_jacobsthal + inserted_numbers;
            bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers - offset);
        }

        prev_jacobsthal = curr_jacobsthal;
        inserted_numbers += jacobsthal_diff;
        offset = 0;
    }

    // 5) Insert remaining pend elements in reverse order
    for (ssize_t i = pend.size() - 1; i >= 0; i--)
    {
        typename std::vector<Iterator>::iterator curr_pend = next(pend.begin(), i);
        typename std::vector<Iterator>::iterator bound_it = next(main.begin(), main.size() - pend.size() + i + is_odd);
        typename std::vector<Iterator>::iterator idx =
            std::upper_bound(main.begin(), bound_it, *curr_pend, _comp<Iterator>);
        main.insert(idx, *curr_pend);
    }

    // 6) Flatten main into copy
    std::vector<int> copy;
    copy.reserve(container.size());
    for (typename std::vector<Iterator>::iterator it = main.begin(); it != main.end(); ++it)
    {
        for (int j = 0; j < pair_level; ++j)
        {
            Iterator pair_start = *it;
            std::advance(pair_start, -pair_level + j + 1);
            copy.push_back(*pair_start);
        }
    }

    // 7) Copy back to container
    Iterator container_it = container.begin();
    for (std::vector<int>::iterator copy_it = copy.begin(); copy_it != copy.end(); ++copy_it)
    {
        *container_it = *copy_it;
        ++container_it;
    }
}


#endif
