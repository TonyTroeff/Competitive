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

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
}

void solve() {
    int l1, b1, l2, b2, l3, b3;
    cin >> l1 >> b1 >> l2 >> b2 >> l3 >> b3;

    bool ok = false;
    if (l2 + l3 == l1 && b2 == b3) ok = b1 + b2 == l1;
    if (!ok && l1 == l2 && l2 == l3) ok = b1 + b2 + b3 == l1;
    if (!ok && b2 + b3 == b1 && l2 == l3) ok = l1 + l2 == b1;
    if (!ok && b1 == b2 && b2 == b3) ok = l1 + l2 + l3 == b1;

    cout << (ok ? "YES" : "NO") << endl;
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
