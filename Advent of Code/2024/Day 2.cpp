#include <bits/stdc++.h>
using namespace std;

#define ll long long

void jump_over(int &index, const int skip) {
    if (index == skip) index++;
}

bool check(const vector<ll> &report, const int skip = -1) {
    if (report.size() < 2) return false;

    int left = 0;
    jump_over(left, skip);
    int right = left + 1;
    jump_over(right, skip);

    const bool increasing = report[right] > report[left];
    while (right < report.size()) {
        const ll diff = report[right] - report[left];

        if (diff == 0 || abs(diff) > 3) return false;
        if (diff > 0 != increasing) return false;

        jump_over(++left, skip);
        jump_over(++right, skip);
    }

    return true;
}

ll solve_part_one(const vector<vector<ll>> &reports) {
    ll ans = 0;

    for (const auto &report: reports) {
        if (check(report)) ans++;
    }

    return ans;
}

ll solve_part_two(const vector<vector<ll>> &reports) {
    ll ans = 0;

    const auto fault_tolerant_check = [](const vector<ll> &report) {
        if (check(report)) return true;
        for (int i = 0; i < report.size(); i++) {
            if (check(report, i)) return true;
        }
        return false;
    };

    for (const auto &report: reports) {
        if (fault_tolerant_check(report)) ans++;
    }

    return ans;
}

int main() {
    ifstream in("Day 2.input.txt");

    vector<vector<ll>> reports;

    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        reports.emplace_back();

        ll num;
        while (iss >> num)
            reports.back().push_back(num);
    }

    cout << "Part one: " << solve_part_one(reports) << endl;
    cout << "Part two: " << solve_part_two(reports) << endl;
}
