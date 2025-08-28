#include <bits/stdc++.h>
using namespace std;

template<typename... T>
class optimized_unordered_map : public unordered_map<T...> {
public:
    template<typename... Args>
    explicit optimized_unordered_map(Args &&... args) : unordered_map<T...>(forward<Args>(args)...) {
        this->reserve(1024);
        this->max_load_factor(0.25);
    }
};

#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))
#define UNKNOWN (-1)

void init() {
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n), b(n);
    for (int &el: a) cin >> el;
    for (int &el: b) cin >> el;

    ll sum = 0;
    for (int i = 0; i < n; i++) sum += min(a[i], b[i]);

    for (int i = 0; i < q; i++) {
        char c;
        int x, v;
        cin >> c >> x >> v;

        const ll prev = min(a[x - 1], b[x - 1]);
        if (c == 'A') a[x - 1] = v;
        else if (c == 'B') b[x - 1] = v;

        const ll current = min(a[x - 1], b[x - 1]);
        sum += current - prev;

        cout << sum << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();
    solve();
}
