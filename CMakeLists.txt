cmake_minimum_required(VERSION 3.8)
project(LogicPractice)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        combination.cpp
        permutation.cpp
        fibonacci.cpp
        bidirectional_search.cpp
        radix_sort.cpp
        quick_sort.cpp insertion_sort.cpp count_sort.cpp select.cpp stream.cpp longest_vaild_parentheses.cpp modular_exponentiation.cpp const_usage.cpp volatile_usage.cpp array.cpp ugly_number.cpp edit_distance.cpp sum_exists.cpp min_jumps.cpp knapsack.cpp parentheses.cpp catalan.cpp even_bin_seq.cpp linear_eq.cpp coin_change.cpp)
add_executable(LogicPractice ${SOURCE_FILES})