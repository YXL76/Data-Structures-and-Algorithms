cmake_minimum_required(VERSION 3.13)
project(Data_Structures_and_Algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories("Data Structures and Algorithms/include")
include_directories("Data Structures and Algorithms/include/algorithm")
include_directories("Data Structures and Algorithms/include/list")
include_directories("Data Structures and Algorithms/include/polynomial")
include_directories("Data Structures and Algorithms/include/queue")
include_directories("Data Structures and Algorithms/include/stack")

add_executable(Data_Structures_and_Algorithms
        "Data Structures and Algorithms/include/algorithm/yxlAlgorithm.h"
        "Data Structures and Algorithms/include/algorithm/yxlStringAlgorithm.h"
        "Data Structures and Algorithms/include/list/yxlArray.h"
        "Data Structures and Algorithms/include/list/yxlChain.h"
        "Data Structures and Algorithms/include/list/yxlList.h"
        "Data Structures and Algorithms/include/polynomial/yxlChainPolynomial.h"
        "Data Structures and Algorithms/include/polynomial/yxlPolynomial.h"
        "Data Structures and Algorithms/include/queue/yxlArrayQueue.h"
        "Data Structures and Algorithms/include/queue/yxlQueue.h"
        "Data Structures and Algorithms/include/stack/yxlArrayStack.h"
        "Data Structures and Algorithms/include/stack/yxlStack.h"
        "Data Structures and Algorithms/include/yxlSegmentTree.h"
        "Data Structures and Algorithms/Data Structures and Algorithms.cpp")
