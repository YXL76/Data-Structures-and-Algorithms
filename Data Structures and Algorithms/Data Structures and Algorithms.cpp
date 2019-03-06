#include <iostream>

#include "yxlArray.h"

yxlArray<int, 10> a(11);

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (auto i = 1; i < 1000; ++i) a.insert(i, i);
    std::cout << a;
    return 0;
}