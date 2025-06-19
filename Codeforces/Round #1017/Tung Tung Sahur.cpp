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

bool solve(const string& p, const string& s) {
    int pi = 0, si = 0;
    while (pi < p.size() && si < s.size()) {
        if (p[pi] != s[si]) return false;

        const int ps = pi, ss = si;
        while (pi + 1 < p.size() && p[pi] == p[pi + 1]) pi++;
        while (si + 1 < s.size() && s[si] == s[si + 1]) si++;

        const int pl = pi - ps + 1, sl = si - ss + 1;

        if (sl < pl || sl > 2 * pl) return false;

        pi++;
        si++;
    }

    return pi == p.size() && si == s.size();
}

void solve() {
    string p, s;
    cin >> p >> s;

    cout << (solve(p, s) ? "YES" : "NO") << endl;
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