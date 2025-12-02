#include <bits/stdc++.h>
using namespace std;

#define ll long long

int count_digits(ll num) {
    int digits_count = 0;
    do {
        digits_count++;
        num /= 10;
    } while (num != 0);
    return digits_count;
}

ll decimal_multiplier(const int magnitude) {
    ll result = 1;
    for (int i = 0; i < magnitude; i++) result *= 10;
    return result;
}

ll repeat_multiplier(const ll magnitude, const int times) {
    ll result = magnitude + 1;
    for (int i = 2; i < times; i++) result = result * magnitude + 1;

    return result;
}

ll solve_part_one(const vector<pair<ll, ll>> &ranges) {
    ll ans = 0;
    for (const auto &[start, end]: ranges) {
        const int digits_count = count_digits(start), digits_to_retain = digits_count / 2;
        ll base = start / decimal_multiplier(digits_count - digits_to_retain), candidate;
        ll magnitude = decimal_multiplier(digits_to_retain), mult = repeat_multiplier(magnitude, 2);
        while ((candidate = base * mult) <= end) {
            if (candidate >= start) ans += candidate;
            if (++base == magnitude) {
                magnitude *= 10;
                mult = repeat_multiplier(magnitude, 2);
            }
        }
    }

    return ans;
}

ll solve_part_two(const vector<pair<ll, ll>> &ranges) {
    ll ans = 0;
    ll base = 0, magnitude = 10, equal_digits_divisor = 1;
    int digits_count = 1;
    bool exceeds_max;
    do {
        base++;
        if (digits_count > 1 && base % equal_digits_divisor == 0) base++;
        if (base == magnitude) {
            digits_count++;
            magnitude *= 10;
            equal_digits_divisor = 10 * equal_digits_divisor + 1;
        }

        exceeds_max = true;

        ll candidate = base;
        for (int repeat_times = 2, index = 0; repeat_times <= 10; repeat_times++) {
            candidate = candidate * magnitude + base;

            while (index < ranges.size() && candidate > ranges[index].second) index++;
            if (index == ranges.size()) break;
            if (digits_count > 1 && repeat_times != 2 && repeat_times != 3 && repeat_times != 5 && repeat_times != 7) continue;

            exceeds_max = false;
            if (candidate >= ranges[index].first) ans += candidate;
        }
    } while (!exceeds_max);

    return ans;
}

int main() {
    ifstream in("Day 2.input.txt");

    vector<pair<ll, ll>> ranges;

    while (!in.eof()) {
        ll start, end;
        in >> start;
        in.ignore(1, '-');
        in >> end;
        in.ignore(1, ',');

        ranges.emplace_back(start, end);
    }

    ranges::sort(ranges);

    cout << "Part one: " << solve_part_one(ranges) << endl;
    cout << "Part two: " << solve_part_two(ranges) << endl;
}
