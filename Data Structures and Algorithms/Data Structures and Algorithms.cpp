#include <iostream>

#include "include/list/yxlArray.h"
#include "include/list/yxlChain.h"
#include "include/queue/yxlArrayQueue.h"
#include "include/stack/yxlArrayStack.h"
#include "include/algorithm/yxlAlgorithm.h"
#include "include/Polynomial/yxlChainPolynomial.h"

yxlArray<int> a(10);
yxlChain<int> b;
yxlArrayQueue<int> c;
yxlArrayStack<int> d;
yxlChainPolynomial e, f;

std::string sss = "ababababca";
std::string ssss = "abababca";
yxlKMP dd(ssss);

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	double a[] = {10, 5, 9, 8, 4, 51, 51, 4};
	double b[] = {46, 4, 6, 1, 61, 64, 1, 61, 61, 6, 2};
	e.read(a, 8);
	f.read(b, 11);
	e.write();
	std::cout << std::endl;
	f.write();
	std::cout << std::endl;
	f += e;
	e.write();
	std::cout << std::endl;
	f.write();
	std::cout << std::endl;
	std::cout << e + f;
	std::cout << std::endl;
	f.write();
	return 0;
}
