#include <iostream>

#include "include/list/yxlArray.h"
#include "include/list/yxlLink.h"
#include "include/queue/yxlArrayQueue.h"
#include "include/stack/yxlArrayStack.h"
#include "include/algorithm/yxlAlgorithm.h"
#include "include/polynomial/yxlArrayPolynomial.h"
#include "include/polynomial/yxlLinkedPolynomial.h"

yxlArray<int> a(10);
yxlLink<int> b;
yxlArrayQueue<int> c;
yxlArrayStack<int> d;
yxlArrayPolynomial e;
yxlLinkedPolynomial f;

std::string sss = "ababababca";
std::string ssss = "abababca";
yxlKMP dd(ssss);

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	double a[4] = {1, 3, 3, 1};
	double b[3] = {1, 2, 1};
	yxlArrayPolynomial x(a, 4);
	yxlArrayPolynomial y(b, 3);
	std::cout << x * y;
	return 0;
}
