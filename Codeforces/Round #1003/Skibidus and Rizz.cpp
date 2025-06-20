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

string solve(const int &n, const int &m, const int &k) {
    const int min_diff = abs(n - m), max_diff = max(n, m);
    if (k < min_diff || k > max_diff) return "-1";

    pair<int, char> p1 = make_pair(n, '0'), p2 = make_pair(m, '1');
    if (m > n) swap(p1, p2);

    string ans(n + m, ' ');
    ans.reserve(n + m);

    for (int i = 0; i < ans.size(); i++) {
        pair<int, char>& curr = (p1.first == 0 || (i >= k && (i - k) % 2 == 0 && p2.first > 0)) ? p2 : p1;

        ans[i] = curr.second;
        curr.first--;
    }

    return ans;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    cout << solve(n, m, k) << endl;
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
