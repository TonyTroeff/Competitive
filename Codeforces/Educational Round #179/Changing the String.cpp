#include <bits/stdc++.h>
using namespace std;

#define ll long long

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    vector ops(3, vector<set<int>>(3));
    for (int i = 0; i < q; i++) {
        char from, to;
        cin >> from >> to;

        ops[from - 'a'][to - 'a'].insert(i);
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == 'b') {
            if (!ops[1][0].empty()) {
                ops[1][0].erase(ops[1][0].begin());
                s[i] = 'a';
            } else if (!ops[1][2].empty()) {
                const auto r1 = ops[1][2].begin();
                const auto r2 = ops[2][0].lower_bound(*r1);
                if (r2 != ops[2][0].end()) {
                    ops[1][2].erase(r1);
                    ops[2][0].erase(r2);
                    s[i] = 'a';
                }
            }
        } else if (s[i] == 'c') {
            if (!ops[2][0].empty()) {
                ops[2][0].erase(ops[2][0].begin());
                s[i] = 'a';
            } else if (!ops[2][1].empty()) {
                const auto r1 = ops[2][1].begin();
                const auto r2 = ops[1][0].lower_bound(*r1);

                ops[2][1].erase(r1);
                if (r2 != ops[1][0].end()) {
                    ops[1][0].erase(r2);
                    s[i] = 'a';
                } else {
                    s[i] = 'b';
                }
            }
        }
    }

    cout << s << endl;
}

int main() {
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
