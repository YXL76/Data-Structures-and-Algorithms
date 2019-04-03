#include <iostream>

#include "include/List/Array.h"
#include "include/List/Link.h"
#include "include/Queue/ArrayQueue.h"
#include "include/Stack/ArrayStack.h"
#include "include/Algorithm/Algorithm.h"
#include "include/Polynomial/ArrayPolynomial.h"
#include "include/Polynomial/LinkedPolynomial.h"
#include "include/BinaryTree/LinkedBinaryTree.h"

using namespace yxl;

int arr[5] = {1, 5, 4, 8, 4};

Array<int> a(10);
Link<int> b;
ArrayQueue<int> c;
ArrayStack<int> d;
ArrayPolynomial e;
LinkedPolynomial f;
LinkedBinaryTree<int> g;

std::string sss = "ababababca";
std::string ssss = "abababca";
KMP dd(ssss);

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	g.build(arr, 5);
	g.print_in_level_order();
	g.remove_left_subtree();
	g.print_in_level_order();
	return 0;
}
