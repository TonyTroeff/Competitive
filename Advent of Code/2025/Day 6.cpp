#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

const unordered_map<char, function<ll(ll, ll)>> operations = {
    {'+', [](const ll a, const ll b) { return a + b; }},
    {'*', [](const ll a, const ll b) { return a * b; }}
};

vector<ll> read_numbers(const string &line) {
    istringstream iss(line);

    vector<ll> numbers;
    ll current_num;
    while (iss >> current_num) numbers.push_back(current_num);

    return numbers;
}

vector<char> read_operators(const string &line) {
    istringstream iss(line);

    vector<char> ops;
    char current_op;
    while (iss >> current_op) ops.push_back(current_op);

    return ops;
}

ll solve_part_one(const vector<string>& grid) {
    int n = UNKNOWN;
    vector<vector<ll>> numbers(grid.size() - 1);
    for (int i = 0; i < grid.size() - 1; i++) {
        const vector<ll> current_row = read_numbers(grid[i]);
        numbers[i] = current_row;

        if (n == UNKNOWN) n = static_cast<int>(current_row.size());
        else if (n != current_row.size()) throw runtime_error("Error: Numeric rows have different sizes");
    }

    const vector<char> operators = read_operators(grid[grid.size() - 1]);
    if (n != operators.size()) throw runtime_error("Error: Operator row size mismatch");

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        const auto operation_it = operations.find(operators[i]);
        if (operation_it == operations.end()) throw runtime_error("Error: Unknown operator");

        const auto& operation = operation_it->second;

        ll result = numbers[0][i];
        for (int j = 1; j < numbers.size(); j++) result = operation(result, numbers[j][i]);

        ans += result;
    }

    return ans;
}

bool read_vertical_number(const vector<string>& grid, const int index, ll& number) {
    number = 0;

    bool had_any_digits = false;
    for (int i = 0; i < grid.size() - 1; i++) {
        if (grid[i][index] >= '0' && grid[i][index] <= '9') {
            number = number * 10 + grid[i][index] - '0';
            had_any_digits = true;
        }
    }

    return had_any_digits;
}

ll solve_part_two(const vector<string>& grid) {
    ll ans = 0;

    const string& operators_row = grid[grid.size() - 1];

    int index = 0;
    while (index < operators_row.size()) {
        const auto operation_it = operations.find(operators_row[index]);
        if (operation_it == operations.end()) throw runtime_error("Error: Unknown operator");

        const auto& operation = operation_it->second;

        bool is_first = true;
        ll result = 0, operand;
        while (read_vertical_number(grid, index, operand)) {
            if (is_first) {
                result = operand;
                is_first = false;
            } else {
                result = operation(result, operand);
            }

            index++;
        }

        ans += result;

        index++;
        while (index < operators_row.size() && operators_row[index] == ' ') index++;
    }

    return ans;
}

int main() {
    ifstream in("Day 6.input.txt");

    vector<string> grid;
    while (!in.eof()) {
        string line;
        getline(in, line);
        grid.push_back(line);
    }

    cout << "Part one: " << solve_part_one(grid) << endl;
    cout << "Part two: " << solve_part_two(grid) << endl;

    return 0;
}
