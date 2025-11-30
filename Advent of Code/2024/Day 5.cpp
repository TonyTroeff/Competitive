#include <bits/stdc++.h>
using namespace std;

#define ll long long

bool check(const unordered_map<ll, vector<ll>> &deps_graph, const vector<ll> &query, unordered_set<ll> &blocked_set) {
    for (const ll &num: query) {
        if (blocked_set.contains(num)) return false;

        const auto &deps_it = deps_graph.find(num);
        if (deps_it == deps_graph.end()) continue;

        for (const ll &predecessor: deps_it->second)
            blocked_set.insert(predecessor);
    }

    return true;
}

bool reorder(const unordered_map<ll, vector<ll>> &deps_graph, vector<ll> &query, unordered_map<ll, unordered_set<ll>> &conflicts_map) {
    bool had_changes = false;
    for (int i = 0; i < query.size(); i++) {
        const ll current_num = query[i];
        if (conflicts_map.contains(current_num)) {
            unordered_set<ll> &conflicts = conflicts_map[current_num];

            int swap_pos = i;
            while (!conflicts.empty()) {
                conflicts.erase(query[swap_pos - 1]);
                swap(query[swap_pos], query[swap_pos - 1]);
                swap_pos--;
            }

            had_changes = true;
        }

        const auto &deps_it = deps_graph.find(current_num);
        if (deps_it == deps_graph.end()) continue;

        for (const ll &predecessor: deps_it->second)
            conflicts_map[predecessor].insert(current_num);
    }

    return had_changes;
}

ll solve_part_one(const unordered_map<ll, vector<ll>> &deps_graph, const vector<vector<ll>> &queries) {
    ll ans = 0;

    unordered_set<ll> blocked_set;
    for (const vector<ll> &query: queries) {
        if (check(deps_graph, query, blocked_set)) ans += query[query.size() / 2];
        blocked_set.clear();
    }

    return ans;
}

ll solve_part_two(const unordered_map<ll, vector<ll>> &deps_graph, vector<vector<ll>> &queries) {
    ll ans = 0;

    unordered_map<ll, unordered_set<ll>> conflicts_map;
    for (vector<ll> &query: queries) {
        if (reorder(deps_graph, query, conflicts_map)) ans += query[query.size() / 2];
        conflicts_map.clear();
    }

    return ans;
}

int main() {
    ifstream in("Day 5.input.txt");

    unordered_map<ll, vector<ll>> deps_graph;

    string line;
    while (getline(in, line)) {
        if (line.empty()) break;

        istringstream iss(line);

        ll a, b;
        iss >> a;
        iss.ignore(1, '|');
        iss >> b;

        deps_graph[b].push_back(a);
    }

    vector<vector<ll>> queries;
    while (getline(in, line)) {
        queries.emplace_back();

        istringstream iss(line);

        ll num;
        while (iss >> num) {
            queries.back().push_back(num);
            iss.ignore(1, ',');
        }
    }

    cout << "Part one: " << solve_part_one(deps_graph, queries) << endl;
    cout << "Part two: " << solve_part_two(deps_graph, queries) << endl;
}
