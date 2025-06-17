#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    vector<int> b(n);
    for (int &el: b) cin >> el;

    vector<pair<int, int>> ops;
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (a[j] > a[j - 1]) break;

            swap(a[j], a[j - 1]);
            ops.emplace_back(1, j);
        }
    }


    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (b[j] > b[j - 1]) break;

            swap(b[j], b[j - 1]);
            ops.emplace_back(2, j);
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) {
            swap(a[i], b[i]);
            ops.emplace_back(3, i + 1);
        }
    }

    cout << ops.size() << endl;
    for (const auto &[op_id, pos]: ops)
        cout << op_id << ' ' << pos << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();

#ifdef SINGLE_TEST
    int t = 1;
#else
    int t;
    cin >> t;
#endif

    while (t--)
        solve();
}
