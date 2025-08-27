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

    string a(n, ' ');
    for (char &el: a) cin >> el;

    int m;
    cin >> m;

    string b(m, ' '), c(m, ' ');
    for (char &el: b) cin >> el;
    for (char &el: c) cin >> el;

    string prefix, suffix;
    prefix.reserve(m);
    suffix.reserve(m);

    for (int i = 0; i < m; i++) {
        if (c[i] == 'V') prefix.push_back(b[i]);
        else suffix.push_back(b[i]);
    }

    ranges::reverse(prefix);
    cout << prefix << a << suffix << endl;
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
