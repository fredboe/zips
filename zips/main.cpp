#include <iostream>
#include <vector>

#include "zips.h"

using namespace zips;

int main()
{
    std::vector<double> vec = {1.2, 3.2, 1.5, 9.2, 0.0, 123.1};
    for (auto [i, elem] : enumerate(std::vector<double>({1.2, 3.2, 1.5, 9.2, 0.0, 123.1})))
    {
        std::cout << i << " " << elem << std::endl;
    }

    std::cout << std::endl;

    for (auto [i,j] : zip2(range(10), vec))
    {
        std::cout << i << " " << j << std::endl;
    }

}