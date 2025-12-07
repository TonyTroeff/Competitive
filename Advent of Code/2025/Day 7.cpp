#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

constexpr char START = 'S';
constexpr char SPLITTER = '^';

pair<int, int> find_start(const int width, const vector<string> &grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == START) return {i, j};
        }
    }

    throw runtime_error("Could not find the starting position");
}

ll solve_part_one(const int width, const vector<string> &grid) {
    const auto [start_row, start_col] = find_start(width, grid);

    vector<bool> current(width), next(width);
    current[start_col] = true;

    ll ans = 0;
    for (int i = start_row + 1; i < grid.size(); i++) {
        for (int j = 0; j < width; j++) {
            if (!current[j]) continue;

            if (grid[i][j] == SPLITTER) {
                ans++;

                if (j > 0) next[j - 1] = true;
                if (j + 1 < width) next[j + 1] = true;
            } else {
                next[j] = true;
            }
        }

        swap(current, next);
        for (int j = 0; j < width; j++) next[j] = false;
    }

    return ans;
}

ll solve_part_two(const int width, const vector<string> &grid) {
    const auto [start_row, start_col] = find_start(width, grid);

    vector<ll> current(width), next(width);
    current[start_col] = 1;

    for (int i = start_row + 1; i < grid.size(); i++) {
        for (int j = 0; j < width; j++) {
            if (current[j] == 0) continue;

            if (grid[i][j] == SPLITTER) {
                if (j > 0) next[j - 1] += current[j];
                if (j + 1 < width) next[j + 1] += current[j];
            } else {
                next[j] += current[j];
            }
        }

        swap(current, next);
        for (int j = 0; j < width; j++) next[j] = 0;
    }

    ll ans = 0;
    for (int i = 0; i < width; i++) ans += current[i];

    return ans;
}

int main() {
    ifstream in("Day 7.input.txt");

    vector<string> grid;
    while (!in.eof()) {
        string line;
        getline(in, line);
        grid.push_back(line);
    }

    const int width = static_cast<int>(grid[0].size());
    for (int i = 1; i < grid.size(); i++) {
        if (width != grid[i].size()) throw runtime_error("Error: Grid rows have different widths");
    }

    cout << "Part one: " << solve_part_one(width, grid) << endl;
    cout << "Part two: " << solve_part_two(width, grid) << endl;

    return 0;
}
