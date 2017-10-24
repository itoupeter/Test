
#include "IntervalSum.h"

#include <fstream>
#include <iostream>

int main()
{
    std::ifstream input("in.txt", std::ios::in);
    std::vector<int> data;
    int i;

    while (input >> i)
    {
        data.push_back(i);
    }

    IntervalSum is(data);

    std::cout << is.Solve(1, 4) << std::endl;

    return 0;
}