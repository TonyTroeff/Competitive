#include <iostream>
using namespace std;

bool solve() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int ones = 0, zeros = 0;
    for (const char &c: s) {
        if (c == '1') ones++;
        else zeros++;
    }

    const int needed_singles = n / 2 - k, rem_zeros = zeros - needed_singles, rem_ones = ones - needed_singles;
    if (rem_zeros < 0 || rem_ones < 0) return false;

    const int good_pairs = rem_zeros / 2 + rem_ones / 2;
    return good_pairs == k;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << (solve() ? "YES" : "NO") << endl;
}
