#include <bits/stdc++.h>
using namespace std;

template <typename... T>
class optimized_unordered_map : public unordered_map<T...> {
public:
    template <typename ...Args>
    explicit optimized_unordered_map(Args&&... args) : unordered_map<T...>(forward<Args>(args)...) {
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
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int total = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1')
            total++;
    }

    cout << (total <= k || n < 2 * k ? "Alice" : "Bob") << endl;
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