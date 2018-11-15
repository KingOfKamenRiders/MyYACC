cmake_minimum_required(VERSION 3.10)
project(MyYACC)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyYACC src/Main.cpp src/cfg/LR_0_item.cpp src/cfg/LR_0_item.h src/fa/LR_1_DFA.cpp src/fa/LR_1_DFA.h src/cfg/CFGParser.cpp src/cfg/CFGParser.h src/cfg/LR_1_item.cpp src/cfg/LR_1_item.h src/cfg/production.h src/util.h)