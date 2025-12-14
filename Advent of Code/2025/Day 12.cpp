#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

constexpr int N = 3;
constexpr int SHAPES_COUNT = 6;
constexpr int ROTATIONS_COUNT = 4;
constexpr char USED = '$';
constexpr char EMPTY = '-';

struct shape {
    vector<pair<int, int>> points;
};

struct composition {
    int width = UNKNOWN, height = UNKNOWN;
    vector<int> expected_shapes;
};

bool can_place(const vector<string> &grid, const shape &s, const int r, const int c) {
    for (const auto &[x, y]: s.points) {
        if (r + x < 0 || r + x >= grid.size() || c + y < 0 || c + y >= grid[r].size() || grid[r + x][c + y] == USED) return false;
    }

    return true;
}

void place(vector<string> &grid, const shape &s, const int r, const int c) {
    for (const auto &[x, y]: s.points)
        grid[r + x][c + y] = USED;
}

void remove(vector<string> &grid, const shape &s, const int r, const int c) {
    for (const auto &[x, y]: s.points)
        grid[r + x][c + y] = EMPTY;
}

bool draw(vector<string> &grid, const int pos, vector<int> &shapes_count, const vector<vector<shape>> &shapes) {
    if (pos == shapes.size()) return true;
    if (shapes_count[pos] == 0) return draw(grid, pos + 1, shapes_count, shapes);

    // NOTE: This is a trivial brute-force solution - try to place each shape on any position. It may be really slow in some edge cases.
    for (int i = 0; i < shapes[pos].size(); i++) {
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[r].size(); c++) {
                if (!can_place(grid, shapes[pos][i], r, c)) continue;

                place(grid, shapes[pos][i], r, c);
                shapes_count[pos]--;
                const bool res = draw(grid, pos, shapes_count, shapes);
                shapes_count[pos]++;
                remove(grid, shapes[pos][i], r, c);

                if (res) return true;
            }
        }
    }

    return false;
}

ll solve_part_one(const vector<composition> &compositions, const vector<vector<shape>> &shapes) {
    ll ans = 0;

    for (int i = 0; i < compositions.size(); i++) {
        vector grid(compositions[i].height, string(compositions[i].width, EMPTY));
        vector shapes_count(compositions[i].expected_shapes);

        const int area = compositions[i].width * compositions[i].height;
        int necessary_cells = 0;
        for (int j = 0; j < shapes_count.size(); j++) necessary_cells += shapes_count[j] * shapes[j][0].points.size();

        if (necessary_cells < area && draw(grid, 0, shapes_count, shapes)) ans++;
    }

    return ans;
}

shape read_shape(istream &in) {
    shape shape{};

    string line;

    // Skip the first line
    getline(in, line);

    // NOTE: All shapes are NxN
    for (int r = 0; r < N; r++) {
        getline(in, line);

        if (line.length() != N) throw runtime_error("Invalid shape.");

        for (int c = 0; c < N; c++) {
            if (line[c] != '#') continue;

            shape.points.emplace_back(r, c);
        }
    }

    // Expect an empty line at the end
    if (!getline(in, line) || !line.empty()) throw runtime_error("Expected an empty line after the shape input.");

    return shape;
}

composition read_composition(istream &in) {
    string line;
    getline(in, line);

    istringstream iss(line);
    composition composition{};

    iss >> composition.width;
    iss.ignore(1, 'x');
    iss >> composition.height;
    iss.ignore(1, ':');

    composition.expected_shapes.reserve(SHAPES_COUNT);
    for (int i = 0, expected_count; i < SHAPES_COUNT && iss >> expected_count; i++)
        composition.expected_shapes.push_back(expected_count);

    if (composition.expected_shapes.size() != SHAPES_COUNT || iss.peek() != EOF) throw runtime_error("Invalid composition.");

    return composition;
}

shape rotate_clockwise(const shape &original) {
    shape rotated{};
    rotated.points.reserve(original.points.size());

    for (const auto &[x, y]: original.points)
        rotated.points.emplace_back(y, N - x - 1);

    return rotated;
}

int main() {
    ifstream in("Day 12.input.txt");

    // NOTE: There are always 6 shapes.
    vector<vector<shape>> shapes;
    shapes.reserve(SHAPES_COUNT);
    for (int i = 0; i < SHAPES_COUNT; i++) {
        shapes.emplace_back(ROTATIONS_COUNT);

        shapes[i][0] = read_shape(in);
        for (int j = 1; j < ROTATIONS_COUNT; j++) shapes[i][j] = rotate_clockwise(shapes[i][j - 1]);
    }

    vector<composition> compositions;
    while (!in.eof()) compositions.push_back(read_composition(in));

    cout << "Part one: " << solve_part_one(compositions, shapes) << endl;
}
