#include <iostream>

#include "include/list/yxlArray.h"
#include "include/list/yxlChain.h"
#include "include/queue/yxlArrayQueue.h"
#include "include/stack/yxlArrayStack.h"
#include "include/algorithm/yxlAlgorithm.h"

yxlArray<int> a(10);
yxlChain<int> b;
yxlArrayQueue<int> c;
yxlArrayStack<int> d;

yxlArray<char> aa;

std::string sss = "ababababca";
std::string ssss = "abababca";

yxlKMP dd(ssss);

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

	std::cout << dd.search(sss);
    return 0;
}
