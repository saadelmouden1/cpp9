#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <deque>
#include <set>
#include "PmergeMe.hpp"

static std::string validation(int argc, char **argv)
{
    if(argc == 1)
        return "No arguments were provide";
    for(int i =1;i< argc; i++)
    {
        if(argv[i][0] == '-')
            return "Negative numbers not allowed";
        long nbr = strtol(argv[i],NULL,10);
        if(nbr == 0 && strcmp(argv[i], "0") != 0)
            return "Non number this is not allowed";
        if(nbr > INT_MAX || errno == ERANGE)
            return "Too big arguments are not allowed";
    }
    return "";
}

static std::vector<int> argv_to_vector(int argc,char **argv){
    
    std::vector<int> vectr;
    vectr.reserve(argc -1);
    for(int i =1; i < argc; i++)
    {
        vectr.push_back(atoi(argv[i]));
    }
    return vectr;
}

static std::set<int> argv_to_set(int argc, char **argv)
{
    std::set<int> res;

    for(int i =1;i < argc; i++)
    {
        res.insert(atoi(argv[i]));
    }
    return res;

}

static void print_vector(std::vector<int> &vectr)
{
    std::cout<<std::endl;
    for(size_t i =0;i< vectr.size(); i++)
    {
        std::cout<<vectr[i] <<",";
    }
    std::cout<<std::endl;
}

static void print_deque(std::deque<int> &dq)
{
    std::cout << std::endl;
    for (size_t i = 0; i < dq.size(); i++)
    {
        std::cout << dq[i] <<",";
    }
    std::cout<<std::endl;
}
static void print_set(std::set<int> &s)
{
    std::cout<<std::endl;
   for(std::set<int>::const_iterator it =s.begin(); it != s.end(); it++)
   {
    std::cout<< *it<<",";
    }
    std::cout<<std::endl;
}

static bool checking_original_values(std::set<int> &originalValues, std::vector<int> &vectr)
{
    for(int i =0 ;i < (int)vectr.size();i++)
    {
        if(originalValues.find(vectr[i]) == originalValues.end())
            return false;
        originalValues.erase(vectr[i]);
    }
    return true;
}

template <typename T> static bool is_sorted(const T& container)
{
    if(container.size() < 2)
        return true;
    //typename T::const_iterator it1 = container.begin();
    typename T::const_iterator end = container.end();
    std::advance(end, -1);
    // ++it2;

    for(typename T::const_iterator it1 = container.begin();it1 != end; it1++)
    {
        typename T::const_iterator nxt  =it1;
        std::advance(nxt,1);
        if(*it1 > *nxt)
            return false;
        // ++it1;
        // ++it2;
    }
    return true;
}
static std::deque<int> argv_to_deque(int argc, char** argv)
{
    std::deque<int> res;
    for (int i = 1; i < argc; i++)
    {
        res.push_back(atoi(argv[i]));
    }
    return res;
}


int main(int argc, char **argv)
{

    PmergeMe pm;

    std::string a =validation(argc,argv);
    std::cout<<a<<std::endl;

    std::set<int> originValues = argv_to_set(argc, argv);

    print_set(originValues);

    std::vector<int> vectr =argv_to_vector(argc, argv);
    print_vector(vectr);

    pm.merge_insertion_sort(vectr, 1);
     std::cout << "After recursive block swaps for vectore:\n";
    print_vector(vectr);
    
    
    if(!is_sorted(vectr) || (int)vectr.size() != (argc - 1) ||!checking_original_values(originValues,vectr))
    {
        std::cout << "Vector was not sorted properly.\n";
		return 1;
    }

     std::deque<int> deque = argv_to_deque(argc, argv);
     print_deque(deque);
     
     pm.merge_insertion_sort(deque, 1);
     std::cout << "After recursive block swaps for deque:\n";
        print_deque(deque);
      if (!is_sorted(deque) || (int)deque.size() != (argc - 1))
	{
        std::cout << "Deque was not sorted properly.\n";
		return 1;
	}
    return 0;
}