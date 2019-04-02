#include <iostream>

#include "include/list/Array.h"
#include "include/list/Link.h"
#include "include/queue/ArrayQueue.h"
#include "include/stack/ArrayStack.h"
#include "include/algorithm/Algorithm.h"
#include "include/polynomial/ArrayPolynomial.h"
#include "include/polynomial/LinkedPolynomial.h"

using namespace yxl;

Array<int> a(10);
Link<int> b;
ArrayQueue<int> c;
ArrayStack<int> d;
ArrayPolynomial e;
LinkedPolynomial f;

std::string sss = "ababababca";
std::string ssss = "abababca";
yxlKMP dd(ssss);

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return 0;
}
