#include <iostream>

#include "include/List/Array.h"
#include "include/List/Link.h"
#include "include/Queue/ArrayQueue.h"
#include "include/Stack/ArrayStack.h"
#include "include/Algorithm.h"
#include "include/Polynomial/ArrayPolynomial.h"
#include "include/Polynomial/LinkedPolynomial.h"
#include "include/BinaryTree/LinkedBinaryTree.h"
#include "include/BinarySearchTree/BinarySearchTree.h"

using namespace yxl;

int arr[18] = {1, 5, 4, 8, 6, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

Array<int> a(10);
Link<int> b;
ArrayQueue<int> c;
ArrayStack<LinkedBinaryTree<int>::tree_node*> d;
ArrayPolynomial e;
LinkedPolynomial f;
LinkedBinaryTree<int> g(arr, 6);
BinarySearchTree<int, int> h;

std::string sss = "ababababca";
std::string ssss = "abababca";
KMP dd(ssss);

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (auto& i : g)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    g.print(LinkedBinaryTree<int>::kIn);
    /*LinkedBinaryTree<int>::ttask aaa = [](LinkedBinaryTree<int>::tree_node*& x){d.push(x);};
    LinkedBinaryTree<int>::ttask bbb = [](LinkedBinaryTree<int>::tree_node*& x){};
    LinkedBinaryTree<int>::ttask ccc = [](LinkedBinaryTree<int>::tree_node*& x){};
    g.t_task(aaa, bbb, ccc);

    d.pop();
    d.pop();
    auto ff = false;
    auto tar = d.top();
    LinkedBinaryTree<int>::ttask aa = [&](LinkedBinaryTree<int>::tree_node*& x)
    {
        if (!ff)   ddd.push(x);
        if (x == tar)  ff = true; 
    };
    LinkedBinaryTree<int>::ttask bb = [&](LinkedBinaryTree<int>::tree_node*& x) {};
    LinkedBinaryTree<int>::ttask cc = [&](LinkedBinaryTree<int>::tree_node*& x)
    {
        if (!ff)   ddd.pop();
    };
    g.t_task(aa, bb, cc);
    while (!ddd.empty())
    {
        std::cout << ddd.top() << ' ';
        ddd.pop();
    }*/
    return 0;
}
