#include <iostream>
#include <vector>
#include <list>

#include "zips.h"

using namespace zips;

template <typename T>
void print_vec(const std::vector<T>& vec)
{
    std::cout << "  [ ";
    for (T elem : vec)
        std::cout << elem << " ";
    std::cout << "]\n";
}

// keep in mind that structured bindings will return references
int main()
{
    std::vector<double> vec1 = {1.2, 3.2, 1.5, 9.2, 0.0, 123.1};
    std::vector<int> vec2 = {1, 2, 5, 10, -1};
    std::list<int> lis3 = {0, 1, 0, 5};
    
    std::cout << std::endl;

    for (auto [i, elem] : enumerate(vec1))
    {
        std::cout << i << " " << elem << std::endl;
    }

    std::cout << std::endl;

    for (auto [i,j] : zip2::zip2(range(10), vec1))
    {
        std::cout << i << " " << j << std::endl;
    }
    
    std::cout << std::endl;

    for (auto [a, b, c] : zip(vec1, vec2, lis3))
    {
        std::cout << a << " " << b << " " << c << std::endl;
    }

    std::cout << std::endl;

    range r(10);

    for (auto [a, b, c] : zip(r, vec2, lis3))
    {
        std::cout << a << " " << b << " " << c << std::endl;
    }

    std::cout << std::endl;

    for (auto [a, b] : zip(vec1, vec2))
    {
        a = 1;
        b = 2;
    }

    print_vec(vec1);
    print_vec(vec2);
}

/* output:
* 0 1.2
* 1 3.2
* 2 1.5
* 3 9.2
* 4 0
* 5 123.1
*
* 0 1.2
* 1 3.2
* 2 1.5
* 3 9.2
* 4 0
* 1.2 1 0
* 3.2 2 1
* 1.5 5 0
* 9.2 10 5
*
* 0 1 0
* 1 2 1
* 2 5 0
* 3 10 5
*
*   [ 1 1 1 1 1 123.1 ]
*   [ 2 2 2 2 2 ]
*/