#include <iostream>

#include "include/array/yxlArray.h"
#include "include/chain/yxlChain.h"
#include "include/queue/yxlArrayQueue.h"
#include "include/stack/yxlArrayStack.h"

yxlArray<int, 10> a(10);
yxlChain<int> b;
yxlArrayQueue<int> c;
yxlArrayStack<int> d;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}
