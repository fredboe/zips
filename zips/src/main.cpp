#include "range.h"
#include "enumerate.h"
#include "zip2.h"
#include <iostream>
#include <functional>
#include <vector>

int inc(int num)
{
    return ++num;
}

// put everywhere move constructors!!!

int main()
{
    std::vector<double> vec = {1.2, 3.2, 1.5, 9.2, 0.0, 123.1};
    /*for (auto [i, elem] : enumerate(std::vector<double>({1.2, 3.2, 1.5, 9.2, 0.0, 123.1})))
    {
        std::cout << i << " " << elem << std::endl;
    }*/

    for (auto [i,j] : zip2(range(10), vec))
    {
        std::cout << i << " " << j << std::endl;
    }

}