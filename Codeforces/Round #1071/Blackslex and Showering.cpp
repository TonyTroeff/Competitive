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

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    int res = 0;
    for (int i = 1; i < n; i++)
        res += abs(a[i] - a[i - 1]);

    int ans = min(res - abs(a[1] - a[0]), res - abs(a[n - 1] - a[n - 2]));
    for (int i = 1; i < n - 1; i++) {
        int candidate = res - abs(a[i] - a[i - 1]) - abs(a[i + 1] - a[i]) + abs(a[i + 1] - a[i - 1]);
        ans = min(ans, candidate);
    }

    cout << ans << endl;
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