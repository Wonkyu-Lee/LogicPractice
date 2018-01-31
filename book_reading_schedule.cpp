//
// Created by blazeq on 2018. 1. 30..
//

#include "catch.hpp"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

namespace sol1 {

class BookReadingSchedule {
private:
    list<int> optimalPath;
    int optimalCost { numeric_limits<int>::max() };
    vector<vector<int>> _g;
    int _days;

public:
    BookReadingSchedule(const vector<int>& pages, int days)
    : _g({pages.size() + 1, vector<int>(pages.size() + 1)})
    , _days(days) {
        buildGraph(pages, days);
        findOptimalPath();
    }

    friend ostream& operator << (ostream& o, const BookReadingSchedule& schedule) {
        if (schedule.optimalPath.empty()) {
            o << "No schedule exists!" << endl;
        } else {
            int day = 1;
            for (auto it = schedule.optimalPath.begin(); it != schedule.optimalPath.end(); ++it) {
                auto next = it; next++;
                int s = *it;
                int e = schedule._g.size() - 1;
                if (next != schedule.optimalPath.end()) {
                    e = *next;
                }

                o << "Day " << day++ <<": ";
                while (s < e) {
                    o << s + 1 << " ";
                    ++s;
                }
                o << endl;
            }
        }
        return o;
    }

private:
    void buildGraph(const vector<int>& pages, int days) {
        int n = pages.size();
        int sum[n + 1];
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + pages[i - 1];
        }

        int avg = round(sum[n] / (float)days);

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (i >= j) {
                    _g[i][j] = -1;
                } else {
                    _g[i][j] = abs(avg - (sum[j] - sum[i]));
                }
            }
        }
    }

    void findOptimalPath() {
        optimalPath.clear();
        optimalCost  = numeric_limits<int>::max();

        list<int> path;
        dfs(0, path, 0);
    }

    void dfs(int u, list<int>& path, int cost) {
        int goal = _g.size() - 1;

        if (u == goal && path.size() == _days) {
            if (cost < optimalCost) {
                optimalCost = cost;
                optimalPath = path;
            }
            return;
        }

        path.push_back(u);
        for (int v = 0; v < _g.size(); ++v) {
            if (_g[u][v] != -1) {
                dfs(v, path, cost + _g[u][v]);
            }
        }
        path.pop_back();
    }
};

} // namespace sol1

namespace sol2 {

void combination(int array[], int s, int e, int result[], int k, int index, function<void(int*, int)> cb) {
    if (index == k) {
        cb(result, k);
        return;
    }

    for (int i = s; k - index <= e - i + 1; ++i) {
        result[index] = array[i];
        combination(array, i + 1, e, result, k, index + 1, cb);
    }
}

void combination(int array[], int n, int k, function<void(int*, int)> cb) {
    int result[k];
    combination(array, 0, n - 1, result, k, 0, cb);
}

// 각 group의 원소를 하나 이상 갖도록 n개를 groups개로 순서를 유지하며 나누기
void allGroupings(int n, int groups, function<void(const list<pair<int, int>>& ranges)> cb) {
    if (n < groups)
        return;

    int gaps[n - 1];
    for (int i = 0; i < n - 1; ++i) {
        gaps[i] = i;
    }

    combination(gaps, n - 1, groups - 1, [n, cb](int* partition, int m){
        list<pair<int, int>> ranges;
        int s = 0;
        for (int i = 0; i < m; ++i) {
            int e = partition[i];
            ranges.emplace_back(s, e);
            s = e + 1;
        }
        ranges.emplace_back(s, n - 1);

        cb(ranges);
    });
}

void printBookReadingSchedule(const vector<int>& pages, int days) {
    int n = pages.size();
    int sum[n];
    sum[0] = 0;
    for (int i = 1; i < n; ++i) {
        sum[i] = sum[i - 1] + pages[i - 1];
    }

    double avg = sum[n - 1] / n;
    double optCost = numeric_limits<double>::infinity();
    list<pair<int, int>> optSchedule;

    allGroupings(pages.size(), days, [&](const list<pair<int, int>>& ranges){
        double cost = 0;
        for (auto& range : ranges) {
            int rangeSum = sum[range.second] - sum[range.first];
            cost += abs(rangeSum - avg);
        }
        if (cost < optCost) {
            optCost = cost;
            optSchedule = ranges;
        }
    });

    for (auto& range : optSchedule) {
        for (int i = range.first; i <= range.second; ++i) {
            printf("%d ", i);
        }
        printf("\n");
    }
    printf("\n");
}



} // namespace sol2

TEST_CASE("Book reading schedule", "[book reading schedule]") {
//    cout << sol1::BookReadingSchedule({8, 5, 6, 12}, 3) << endl;
//    cout << sol1::BookReadingSchedule({10, 5, 5}, 2) << endl;

//    sol2::allGroupings(5, 3, [](const list<pair<int, int>>& ranges) {
//        for (auto& range : ranges) {
//            printf("(%d, %d)", range.first, range.second);
//        }
//        printf("\n");
//    });

    sol2::printBookReadingSchedule({8, 5, 6, 12}, 3);
    sol2::printBookReadingSchedule({10, 5, 5}, 2);
}