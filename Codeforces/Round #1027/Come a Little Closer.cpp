#include <iostream>
#include <map>
#include <vector>
using namespace std;

template<typename Iterator>
void increment(Iterator &it) { ++it; }

template<typename Iterator>
void decrement(Iterator &it) { --it; }

template<typename Iterator>
void validate(const Iterator& it, int& index, bool& is_valid) {
    if (!is_valid) return;

    if (it->second.size() != 1) {
        is_valid = false;
        return;
    }

    if (index == -1) index = it->second[0];
    else if (index != it->second[0]) is_valid = false;
}

template<typename... Ts>
void try_add_solution(const auto &max_h, const auto &min_h, const auto &max_v, const auto &min_v,
                      vector<pair<int, int>> &candidate_solutions, Ts &... changes) {
    int index = -1;
    bool valid = true;
    (validate(changes, index, valid), ...);

    if (!valid) return;

    (increment(changes), ...);

    candidate_solutions.emplace_back(max_h->first - min_h->first + 1, max_v->first - min_v->first + 1);

    (decrement(changes), ...);
}

long long solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> monsters(n);
    for (auto &[x, y]: monsters) cin >> x >> y;

    map<int, vector<int>> horizontal, vertical;
    for (int i = 0; i < n; i++) {
        horizontal[monsters[i].first].push_back(i);
        vertical[monsters[i].second].push_back(i);
    }

    vector<pair<int, int>> candidate_solutions;
    auto max_h = horizontal.rbegin();
    auto min_h = horizontal.begin();
    auto max_v = vertical.rbegin();
    auto min_v = vertical.begin();

    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions);
    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions, max_h);
    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions, min_h);
    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions, max_v);
    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions, min_v);
    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions, max_h, max_v);
    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions, max_h, min_v);
    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions, min_h, max_v);
    try_add_solution(max_h, min_h, max_v, min_v, candidate_solutions, min_h, min_v);

    long long res = LONG_LONG_MAX;
    for (const auto &[x,y]: candidate_solutions) {
        long long candidate = 1LL * x * y;
        if (candidate < n) candidate += min(x, y);
        res = min(res, candidate);
    }

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
