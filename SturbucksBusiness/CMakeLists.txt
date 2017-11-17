cmake_minimum_required(VERSION 3.5.1)
project(project2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Order.cpp Order.h CashierQueue.cpp CashierQueue.h Cashier.cpp Cashier.h BaristaQueue.cpp BaristaQueue.h Barista.cpp Barista.h Algorithm.cpp Algorithm.h)
add_executable(project2 ${SOURCE_FILES})
