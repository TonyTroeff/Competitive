#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

constexpr char PAPER_ROLL = '@';

int count_surrounding(const vector<string> &grid, const int row, const int col) {
    int res = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            if (const int r = row + i, c = col + j; r >= 0 && r < grid.size() && c >= 0 && c < grid[r].size() && grid[r][c] == PAPER_ROLL) res++;
        }
    }

    return res;
}

bool find_accessible_paper_rolls(const vector<string>& grid, vector<pair<int, int>>& accessible_paper_rolls) {
    accessible_paper_rolls.clear();
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == PAPER_ROLL && count_surrounding(grid, i, j) < 4) accessible_paper_rolls.emplace_back(i, j);
        }
    }

    return !accessible_paper_rolls.empty();
}

ll solve_part_one(const vector<string> &grid) {
    vector<pair<int, int>> accessible_paper_rolls;
    find_accessible_paper_rolls(grid, accessible_paper_rolls);
    return static_cast<ll>(accessible_paper_rolls.size());
}

ll solve_part_two(const vector<string>& grid) {
    ll ans = 0;
    vector<string> modifiable_grid_copy = grid;

    vector<pair<int, int>> accessible_paper_rolls;
    while (find_accessible_paper_rolls(modifiable_grid_copy, accessible_paper_rolls)) {
        for (const auto[row, col]:accessible_paper_rolls)
            modifiable_grid_copy[row][col] = '.';

        ans += static_cast<ll>(accessible_paper_rolls.size());
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
