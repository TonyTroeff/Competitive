#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
}

void solve() {
    ull n, k;
    cin >> n >> k;

    vector<ull> a(n);
    for (ull &el: a) cin >> el;

    priority_queue<ull, vector<ull>, greater<>> pq;
    int beauty = 0;
    for (const ull &el: a) {
        ull t = el, additive = 1;
        for (int i = 0; i < 64; i++, additive <<= 1, t >>= 1) {
            if (t & 1) beauty++;
            else pq.push(additive);
        }
    }

    while (!pq.empty()) {
        const ull cost = pq.top();
        pq.pop();

        if (cost > k) break;

        k -= cost;
        beauty++;
    }

    cout << beauty << endl;
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
