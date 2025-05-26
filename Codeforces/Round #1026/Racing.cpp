#include <iostream>
#include <vector>
using namespace std;

bool narrow_ranges(const int n, const vector<int> &d, vector<pair<int, int>> &r) {
    int min_h = 0, max_h = 0;

    for (int i = 0; i < n; i++) {
        if (d[i] == 1) min_h++;
        if (d[i] != 0) max_h++;

        if (r[i].first > max_h || r[i].second < min_h) return false;

        min_h = max(min_h, r[i].first);
        max_h = min(max_h, r[i].second);
        r[i] = {min_h, max_h};
    }

    return true;
}

vector<int> solve() {
    int n;
    cin >> n;

    vector<int> d(n);
    for (int &el: d) cin >> el;

    vector<pair<int, int>> r(n);
    for (int i = 0; i < n; i++) {
        int l, h;
        cin >> l >> h;
        r[i] = {l, h};
    }

    if (!narrow_ranges(n, d, r)) return {-1};

    for (int i = n - 2; i >= 0; i--) {
        int lower = r[i + 1].first;
        if (d[i + 1] != 0) lower--;

        int upper = r[i + 1].second;
        if (d[i + 1] == 1) upper++;

        r[i] = {max(r[i].first, lower), min(r[i].second, upper)};
    }

    int h = 0;
    for (int i = 0; i < n; i++) {
        if (d[i] == 1) h++;
        else if (d[i] == -1) {
            if (h < r[i].first) {
                h++;
                d[i] = 1;
            } else {
                d[i] = 0;
            }
        }
    }

    return d;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        const vector<int> res = solve();
        for (const int &el: res) cout << el << ' ';
        cout << endl;
    }
}
