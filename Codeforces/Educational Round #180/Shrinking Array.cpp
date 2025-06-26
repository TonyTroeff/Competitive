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

int solve(const vector<int> &a) {
    for (int i = 1; i < a.size(); i++) {
        if (abs(a[i] - a[i - 1]) <= 1) return 0;
    }

    for (int i = 2; i < a.size(); i++) {
        if (a[i - 1] > a[i - 2] == a[i - 1] > a[i])
            return 1;
    }

    return -1;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    cout << solve(a) << endl;
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
