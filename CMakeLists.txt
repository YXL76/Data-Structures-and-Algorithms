cmake_minimum_required(VERSION 3.14)
project(my_cpp_library)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "clang++")

include_directories(my-cpp-library/include)
include_directories(my-cpp-library/include/Algorithm)
include_directories(my-cpp-library/include/BinarySearchTree)
include_directories(my-cpp-library/include/BinaryTree)
include_directories(my-cpp-library/include/Dictionary)
include_directories(my-cpp-library/include/Heap)
include_directories(my-cpp-library/include/Huffman)
include_directories(my-cpp-library/include/List)
include_directories(my-cpp-library/include/Polynomial)
include_directories(my-cpp-library/include/Queue)
include_directories(my-cpp-library/include/Stack)

add_executable(my_cpp_library
        my-cpp-library/include/Algorithm/StringAlgorithm.h
        my-cpp-library/include/BinarySearchTree/BinarySearchTree.h
        my-cpp-library/include/BinaryTree/BinaryTree.h
        my-cpp-library/include/BinaryTree/BinaryTreeTask.h
        my-cpp-library/include/BinaryTree/LinkedBinaryTree.h
        my-cpp-library/include/BinaryTree/LinkedBinaryTreeNode.h
        my-cpp-library/include/Dictionary/Dictionary.h
        my-cpp-library/include/Heap/Heap.h
        my-cpp-library/include/Heap/MaxHeap.h
        my-cpp-library/include/Heap/MinHeap.h
        my-cpp-library/include/Huffman/HuffmanTree.h
        my-cpp-library/include/List/Array.h
        my-cpp-library/include/List/Link.h
        my-cpp-library/include/List/LinkNode.h
        my-cpp-library/include/List/List.h
        my-cpp-library/include/Polynomial/ArrayPolynomial.h
        my-cpp-library/include/Polynomial/LinkedPolynomial.h
        my-cpp-library/include/Polynomial/Polynomial.h
        my-cpp-library/include/Queue/ArrayQueue.h
        my-cpp-library/include/Queue/Queue.h
        my-cpp-library/include/Stack/ArrayStack.h
        my-cpp-library/include/Stack/Stack.h
        my-cpp-library/include/Algorithm.h
        my-cpp-library/Source.cpp)
