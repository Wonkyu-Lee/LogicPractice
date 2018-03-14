//
// Created by blazeq on 2018. 2. 26..
//

#include <unordered_set>
#include <queue>
#include <iostream>
#include "catch.hpp"


// https://ide.geeksforgeeks.org/0x8SWY7nsh

using namespace std;

namespace {

using Matrix = vector<vector<int>>;

class Context
{
    const Matrix& times;
    vector<int> minTimeForTask;
    int minTime{INT_MAX};
    unordered_set<int> assignedPeople;
    int callCount{0};

public:
    Context(const Matrix& times) : times(times), minTimeForTask(times.size())
    {
        int n = times.size();
        for (int t = 0; t < n; ++t) {
            minTimeForTask[t] = INT_MAX;
            for (int p = 0; p < n; ++p) {
                minTimeForTask[t] = min(minTimeForTask[t], times[p][t]);
            }
        }
    }

    int minTimeSum() const
    {
        int sum = 0;
        for (auto time : minTimeForTask) {
            sum += time;
        }
        return sum;
    }

    struct Expectation {
        int person;
        int fromStart;
        int toEnd;

        Expectation(const Context& context, int p, int t, int fromStart, int toEnd) {
            person = p;
            this->fromStart = fromStart + context.times[p][t];
            this->toEnd = toEnd - context.minTimeForTask[t];
        }

        int value() const {
            return fromStart + toEnd;
        }
    };
    using ExpectationPtr = shared_ptr<Expectation>;

    void assignTask(int taskIndex, int fromStart, int toEnd)
    {
        callCount++;

        int n = times.size();
        if (taskIndex == n) {
            minTime = min(minTime, fromStart);
            return;
        }

        auto compare = [](const ExpectationPtr& e1, const ExpectationPtr& e2) {
            return e1->value() > e2->value();
        };

        priority_queue<ExpectationPtr, vector<ExpectationPtr>, decltype(compare)> minHeap(compare);

        for (int p = 0; p < n; ++p) {
            if (assignedPeople.find(p) == assignedPeople.end()) {
                minHeap.push(make_shared<Expectation>(*this, p, taskIndex, fromStart, toEnd));
            }
        }

        while (!minHeap.empty()) {
            auto expectation = minHeap.top();
            minHeap.pop();

            if (expectation->value() >= minTime) {
                continue;
            }

            assignedPeople.insert(expectation->person);
            assignTask(taskIndex + 1, expectation->fromStart, expectation->toEnd);
            assignedPeople.erase(expectation->person);
        }
    }

    int getMinTime() const {
        cout << "Call count: " << callCount << endl;
        return minTime;
    }
};

int getMinTime(const Matrix& times)
{
    Context context(times);
    context.assignTask(0, 0, context.minTimeSum());
    return context.getMinTime();
}

} // namespace

TEST_CASE("Task assignment", "[task_assignment]") {
    //Matrix times({{2, 1, 2}, {9, 8, 1}, {1, 1, 1}});
    //cout << getMinTime(times) << endl;
}