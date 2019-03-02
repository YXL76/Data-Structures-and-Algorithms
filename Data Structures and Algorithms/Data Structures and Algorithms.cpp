#include <iostream>

#include "yxlArray.h"

yxlArray<int, 10> a(11);

int main()
{
    a[5] = 2;
    std::cout << a[5];
    return 0;
}