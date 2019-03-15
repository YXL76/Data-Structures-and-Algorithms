cmake_minimum_required(VERSION 3.13)
project(Data_Structures_and_Algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories("Data Structures and Algorithms/include")
include_directories("Data Structures and Algorithms/include/array")
include_directories("Data Structures and Algorithms/include/chain")
include_directories("Data Structures and Algorithms/include/queue")
include_directories("Data Structures and Algorithms/include/stack")

add_executable(Data_Structures_and_Algorithms
        "Data Structures and Algorithms/include/array/yxlArray.h"
        "Data Structures and Algorithms/include/array/yxlList.h"
        "Data Structures and Algorithms/include/chain/yxlChain.h"
        "Data Structures and Algorithms/include/chain/yxlList.h"
        "Data Structures and Algorithms/include/queue/yxlArrayQueue.h"
        "Data Structures and Algorithms/include/queue/yxlQueue.h"
        "Data Structures and Algorithms/include/stack/yxlArrayStack.h"
        "Data Structures and Algorithms/include/stack/yxlStack.h"
        "Data Structures and Algorithms/include/yxlAlgorithm.h"
        "Data Structures and Algorithms/include/yxlSegmentTree.h"
        "Data Structures and Algorithms/Data Structures and Algorithms.cpp")
