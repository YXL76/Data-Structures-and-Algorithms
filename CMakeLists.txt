cmake_minimum_required(VERSION 3.13)
project(Data_Structures_and_Algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories("Data Structures and Algorithms/include")
include_directories("Data Structures and Algorithms/include/Algorithm")
include_directories("Data Structures and Algorithms/include/BinaryTree")
include_directories("Data Structures and Algorithms/include/List")
include_directories("Data Structures and Algorithms/include/Polynomial")
include_directories("Data Structures and Algorithms/include/Queue")
include_directories("Data Structures and Algorithms/include/Stack")

add_executable(Data_Structures_and_Algorithms
        "Data Structures and Algorithms/include/Algorithm/Algorithm.h"
        "Data Structures and Algorithms/include/Algorithm/StringAlgorithm.h"
        "Data Structures and Algorithms/include/BinaryTree/BinaryTree.h"
        "Data Structures and Algorithms/include/BinaryTree/BinaryTreeTask.h"
        "Data Structures and Algorithms/include/BinaryTree/LinkedBinaryTree.h"
        "Data Structures and Algorithms/include/BinaryTree/LinkedBinaryTreeNode.h"
        "Data Structures and Algorithms/include/List/Array.h"
        "Data Structures and Algorithms/include/List/Link.h"
        "Data Structures and Algorithms/include/List/LinkNode.h"
        "Data Structures and Algorithms/include/List/List.h"
        "Data Structures and Algorithms/include/Polynomial/ArrayPolynomial.h"
        "Data Structures and Algorithms/include/Polynomial/LinkedPolynomial.h"
        "Data Structures and Algorithms/include/Polynomial/Polynomial.h"
        "Data Structures and Algorithms/include/Queue/ArrayQueue.h"
        "Data Structures and Algorithms/include/Queue/Queue.h"
        "Data Structures and Algorithms/include/Stack/ArrayStack.h"
        "Data Structures and Algorithms/include/Stack/Stack.h"
        "Data Structures and Algorithms/include/SegmentTree.h"
        "Data Structures and Algorithms/Source.cpp")
