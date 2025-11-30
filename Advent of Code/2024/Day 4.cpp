#include <bits/stdc++.h>
using namespace std;

#define ll long long

constexpr string XMAS = "XMAS";
constexpr string MAS = "MAS";

bool find(const string &search_term, const vector<string> &grid, const int start_row, const int start_col, const int row_change, const int col_change) {
    for (int i = 0; i < search_term.length(); i++) {
        const int row = start_row + row_change * i, col = start_col + col_change * i;
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[row].size() || grid[row][col] != search_term[i]) return false;
    }

    return true;
}

ll solve_part_one(const vector<string> &grid) {
    ll ans = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            ans += find(XMAS, grid, i, j, 1, 0) + find(XMAS, grid, i, j, -1, 0);
            ans += find(XMAS, grid, i, j, 0, 1) + find(XMAS, grid, i, j, 0, -1);
            ans += find(XMAS, grid, i, j, 1, 1) + find(XMAS, grid, i, j, -1, -1);
            ans += find(XMAS, grid, i, j, 1, -1) + find(XMAS, grid, i, j, -1, 1);
        }
    }

    return ans;
}


ll solve_part_two(const vector<string> &grid) {
    ll ans = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            ans += find(MAS, grid, i, j, 1, 1) && find(MAS, grid, i + 2, j, -1, 1);
            ans += find(MAS, grid, i, j, 1, -1) && find(MAS, grid, i + 2, j, -1, -1);
            ans += find(MAS, grid, i, j, 1, 1) && find(MAS, grid, i, j + 2, 1, -1);
            ans += find(MAS, grid, i, j, -1, 1) && find(MAS, grid, i, j + 2, -1, -1);
        }
    }

    return ans;
}

int main() {
    ifstream in("Day 4.input.txt");

    vector<string> grid;

    string line;
    while (getline(in, line)) grid.push_back(line);

    cout << "Part one: " << solve_part_one(grid) << endl;
    cout << "Part two: " << solve_part_two(grid) << endl;
}
