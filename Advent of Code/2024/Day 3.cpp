#include <bits/stdc++.h>
using namespace std;

#define ll long long

bool try_advance(const char symbol, const char expected, int &current_state, const int next_state) {
    if (symbol == expected) {
        current_state = next_state;
        return true;
    }

    return false;
}

bool try_read_operand_or_advance(const char symbol, int &operand_length, ll &operand, const char expected, int &current_state, const int next_state) {
    if (isdigit(symbol)) {
        if (operand_length < 3) {
            operand = operand * 10 + symbol - '0';
            operand_length++;
            return true;
        }

        return false;
    }

    return try_advance(symbol, expected, current_state, next_state);
}

ll solve_part_one(const vector<string> &lines) {
    ll ans = 0;

    for (const string &line: lines) {
        int index = 0, state = 0, first_operand_length = 0, second_operand_length = 0;
        ll first_operand = 0, second_operand = 0;

        while (index < line.size()) {
            bool keep_going = false;
            if (state == 0) keep_going = try_advance(line[index], 'm', state, 1);
            else if (state == 1) keep_going = try_advance(line[index], 'u', state, 2);
            else if (state == 2) keep_going = try_advance(line[index], 'l', state, 3);
            else if (state == 3) keep_going = try_advance(line[index], '(', state, 4);
            else if (state == 4) keep_going = try_read_operand_or_advance(line[index], first_operand_length, first_operand, ',', state, 5);
            else if (state == 5) {
                keep_going = try_read_operand_or_advance(line[index], second_operand_length, second_operand, ')', state, 6);
                if (keep_going && state == 6) {
                    ans += first_operand * second_operand;
                    keep_going = false;
                }
            }

            if (!keep_going) {
                state = 0;
                first_operand_length = 0;
                first_operand = 0;
                second_operand_length = 0;
                second_operand = 0;
            }

            index++;
        }
    }

    return ans;
}

ll solve_part_two(const vector<string> &lines) {
    ll ans = 0;
    bool enabled = true;

    for (const string &line: lines) {
        int index = 0, state = 0, first_operand_length = 0, second_operand_length = 0;
        ll first_operand = 0, second_operand = 0;

        while (index < line.size()) {
            bool keep_going = false;
            if (state == 0) keep_going = (enabled && try_advance(line[index], 'm', state, 1)) || try_advance(line[index], 'd', state, 7);
            else if (state == 1) keep_going = try_advance(line[index], 'u', state, 2);
            else if (state == 2) keep_going = try_advance(line[index], 'l', state, 3);
            else if (state == 3) keep_going = try_advance(line[index], '(', state, 4);
            else if (state == 4) keep_going = try_read_operand_or_advance(line[index], first_operand_length, first_operand, ',', state, 5);
            else if (state == 5) {
                keep_going = try_read_operand_or_advance(line[index], second_operand_length, second_operand, ')', state, 6);
                if (keep_going && state == 6) {
                    ans += first_operand * second_operand;
                    keep_going = false;
                }
            } else if (state == 7) keep_going = try_advance(line[index], 'o', state, 8);
            else if (state == 8) keep_going = try_advance(line[index], '(', state, 9) || try_advance(line[index], 'n', state, 10);
            else if (state == 9) {
                if (try_advance(line[index], ')', state, -1)) enabled = true;
            } else if (state == 10) keep_going = try_advance(line[index], '\'', state, 11);
            else if (state == 11) keep_going = try_advance(line[index], 't', state, 12);
            else if (state == 12) keep_going = try_advance(line[index], '(', state, 13);
            else if (state == 13) {
                if (try_advance(line[index], ')', state, -1)) enabled = false;
            }

            if (!keep_going) {
                state = 0;
                first_operand_length = 0;
                first_operand = 0;
                second_operand_length = 0;
                second_operand = 0;
            }

            index++;
        }
    }

    return ans;
}

int main() {
    ifstream in("Day 3.input.txt");

    vector<string> lines;

    string line;
    while (getline(in, line)) lines.push_back(line);

    cout << "Part one: " << solve_part_one(lines) << endl;
    cout << "Part two: " << solve_part_two(lines) << endl;
}
