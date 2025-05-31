#include <iostream>
#include <vector>
using namespace std;

#define MAX_N (2 * 1e5)

int cache_id = 1;
vector<int> cache(MAX_N + 1);

int count(const int m, const vector<int> &a) {
    cache_id++;

    int groups = 0, pos = 0;
    for (const int& el : a) {
        if (el < m) cache[el] = cache_id;

        while (pos < m && cache[pos] == cache_id) pos++;
        if (pos == m) {
            pos = 0;
            groups++;
            cache_id++;
        }
    }

    return groups;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    int l = 0, h = n;
    while (l <= h) {
        const int m = l + (h - l) / 2;

        if (count(m, a) >= k) l = m + 1;
        else h = m - 1;
    }

    cout << h << endl;
}

int main() {
    int t;
    cin >> t;

    while (t--) solve();
}
