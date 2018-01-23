//
// Created by blazeq on 2018. 1. 21..
//

#include "catch.hpp"
#include <list>
#include <iostream>

namespace {

using namespace std;

list<int> searchUsingStd(const string& str, const string& pattern) {
    list<int> result;
    size_t found = str.find(pattern);
    while (found != string::npos) {
        result.push_back(found);
        found = str.find(pattern, found + 1);
    }

    return result;
}

list<int> searchUsingFA(const string& str, const string& pattern) {
    list<int> result;

    int stateCount = pattern.length() + 1;
    int alphabetCount = 128;
    int goalState = stateCount - 1;

    int automata[stateCount][alphabetCount];
    memset(automata, 0, sizeof(automata));

    auto getNextState = [&](int state, int alphabet) {
        if (state < goalState && pattern[state] == alphabet)
            return state + 1;

        for (int nextState = state; 1 <= nextState; --nextState) {
            if (pattern[nextState - 1] == alphabet) {
                bool matched = true;
                for (int i = 0; i < nextState - 1; ++i) {
                    if (pattern[i] != pattern[state - nextState + 1 + i]) {
                        matched = false;
                    }
                }
                if (matched) {
                    return nextState;
                }
            }
        }

        return 0;
    };

    // build automata
    for (int state = 0; state < stateCount; ++state) {
        for (int alphabet = 0; alphabet < alphabetCount; ++alphabet) {
            automata[state][alphabet] = getNextState(state, alphabet);
        }
    }

    // match
    int currentState = 0;
    for (int i = 0; i < str.length(); ++i) {
        currentState = automata[currentState][str[i]];
        if (currentState == goalState) {
            result.push_back(i - pattern.length() + 1);
        }
    }

    return result;
}

} // namespace

TEST_CASE("Pattern matching using finite automata", "[pattern matching fa]") {
    string str = "There are two needles in this haystack with needles.";
    string pattern = "needle";

    using Method = function<list<int>(const string&, const string&)>;
    auto print = [&](Method method) {
        auto result = method(str, pattern);
        for (auto e : result) {
            cout << e << " ";
        }
        cout << endl;
    };

    SECTION("Using string method") {
        print(searchUsingStd);
    }

    SECTION("Using Finite Automata") {
        print(searchUsingFA);
    }
}