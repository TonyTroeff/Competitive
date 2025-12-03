#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

ll solve_part_one(const vector<string> &banks) {
    ll ans = 0;
    for (const string &bank: banks) {
        int max_prev_digit = bank[bank.length() - 1] - '0';
        ll max_num = 0;
        for (int i = static_cast<int>(bank.length()) - 2; i >= 0; i--) {
            const int current_digit = bank[i] - '0';
            const ll current_num = current_digit * 10 + max_prev_digit;

            max_num = max(current_num, max_num);
            max_prev_digit = max(current_digit, max_prev_digit);
        }

        ans += max_num;
    }

    return ans;
}

ll solve_part_two(const vector<string>& banks) {
    ll ans = 0;

    for (const string& bank: banks) {
        ll current_num = 0;
        int pos = 0, redundant_count = static_cast<int>(bank.length() - 12);
        for (int i = 0; i < 12; i++) {
            int max_pos = pos;
            for (int j = 1; j <= redundant_count; j++) {
                if (bank[pos + j] > bank[max_pos]) max_pos = pos + j;
            }

            current_num = current_num * 10 + bank[max_pos] - '0';
            redundant_count -= max_pos - pos;
            pos = max_pos + 1;
        }

        ans += current_num;
    }

    return ans;
}

int main() {
    ifstream in("Day 3.input.txt");

    vector<string> banks;

    string line;
    while (getline(in, line)) banks.push_back(line);

    cout << "Part one: " << solve_part_one(banks) << endl;
    cout << "Part two: " << solve_part_two(banks) << endl;
}
