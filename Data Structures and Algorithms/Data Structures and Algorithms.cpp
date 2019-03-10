#include <iostream>

#include "yxlChain.h"
#include "yxlArray.h"

yxlChain<int> a;
yxlArray<int, 10> c(10);

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    a.insert(0, 0);
    a.insert(1, 1);
    a.insert(2, 2);
    a.insert(3, 3);
    a.insert(4, 4);
    a.insert(2, 5);
    a.insert(2, 6);
    auto b = a;
    a.erase(2);
    for (auto & i : b)
        std::cout << i.value << ' ';
    return 0;
}