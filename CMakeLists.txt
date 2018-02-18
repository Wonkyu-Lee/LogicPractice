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
        quick_sort.cpp insertion_sort.cpp count_sort.cpp select.cpp stream.cpp longest_vaild_parentheses.cpp modular_exponentiation.cpp const_usage.cpp volatile_usage.cpp array.cpp ugly_number.cpp edit_distance.cpp sum_exists.cpp min_jumps.cpp knapsack.cpp parentheses.cpp catalan.cpp even_bin_seq.cpp linear_eq.cpp coin_change.cpp all_k_size_subsets_with_target_sum.cpp partitioning.cpp divide_string_large_number.cpp count_bst_nodes_in_given_range.cpp graph_coloring.cpp a_star_path_finding.cpp pattern_matching_finite_automata.cpp subarrays_with_target_sum.cpp graph_search.cpp stock_buy_sell.cpp eratosthenes.cpp book_reading_schedule.cpp distance_to_greater.cpp minimize_cash_flow.cpp shift_operator.cpp next_greater_element.cpp stock_span.cpp max_of_mins_for_each_window.cpp iterative_dfs.cpp dice_straight.cpp largest_rectangluar_area_in_histogram.cpp inclusion.cpp binary_search_tree.cpp min_bracket_reversals.cpp duplicate_parenthesis.cpp minimum_spanning_tree.cpp sudoku.cpp)
add_executable(LogicPractice ${SOURCE_FILES})