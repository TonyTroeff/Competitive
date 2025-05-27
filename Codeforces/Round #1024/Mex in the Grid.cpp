#include <iostream>
#include <vector>
using namespace std;

vector directions{0, 1, 0, -1, 0};

vector<vector<int>> solve() {
    int n;
    cin >> n;

    int number = n * n - 1, row = 0, col = 0, direction_index = 0;
    vector res(n, vector<int>(n));

    while (number >= 0) {
        res[row][col] = number;

        int nextRow = row + directions[direction_index], nextCol = col + directions[direction_index + 1];
        if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= n || res[nextRow][nextCol] > number) {
            direction_index = (direction_index + 1) % 4;
            nextRow = row + directions[direction_index];
            nextCol = col + directions[direction_index + 1];
        }

        row = nextRow;
        col = nextCol;
        number--;
    }

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        const vector<vector<int>> matrix = solve();
        for (const auto & row : matrix) {
            for (const int& cell : row)
                cout << cell << ' ';

            cout << endl;
        }
    }
}
