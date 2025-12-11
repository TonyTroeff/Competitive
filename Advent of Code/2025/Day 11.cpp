#include <strstream>
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

constexpr string START = "you";
constexpr string END = "out";
constexpr string SERVER = "svr";
constexpr string DIGITAL_TO_ANALOG_CONVERTER = "dac";
constexpr string FAST_FOURIER_TRANSFORM = "fft";

ll solve_part_one(const unordered_map<string, vector<string>> &graph) {
    queue<string> q;
    q.emplace(START);

    ll ans = 0;

    while (!q.empty()) {
        const string current = q.front();
        q.pop();

        const auto it = graph.find(current);
        if (it == graph.end()) throw runtime_error("Error: Unknown node");

        for (const string &next: it->second) {
            if (next == END) ans++;
            else q.emplace(next);
        }
    }

    return ans;
}

ll count_paths(const unordered_map<string, vector<string>> &graph, const string& node, const uint8_t state, map<pair<string, uint8_t>, ll> & memo) {
    if (node == END) return state == 3;

    const pair key(node, state);
    if (memo.contains(key)) return memo[key];

    uint8_t next_state = state;
    if (node == DIGITAL_TO_ANALOG_CONVERTER) next_state |= 1;
    else if (node == FAST_FOURIER_TRANSFORM) next_state |= 2;

    const auto it = graph.find(node);
    if (it == graph.end()) throw runtime_error("Error: Unknown node");

    ll ans = 0;
    for (const string &next: it->second) {
        if (next == END) ans += state == 3;
        else ans += count_paths(graph, next, next_state, memo);
    }

    return memo[key] = ans;
}

ll solve_part_two(const unordered_map<string, vector<string>> &graph) {
    map<pair<string, uint8_t>, ll> memo;
    return count_paths(graph, SERVER, 0, memo);
}

int main() {
    ifstream in("Day 11.input.txt");

    unordered_map<string, vector<string>> graph;
    string line;
    while (getline(in, line)) {
        istringstream iss(line);

        string from;
        getline(iss, from, ':');

        string to;
        while (iss >> to) graph[from].push_back(to);
    }

    cout << "Part one: " << solve_part_one(graph) << endl;
    cout << "Part two: " << solve_part_two(graph) << endl;
}
