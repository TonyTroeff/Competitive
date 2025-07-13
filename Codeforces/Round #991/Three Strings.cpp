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
    string a, b, c;
    cin >> a >> b >> c;

    vector dp(a.length() + 1, vector(b.length() + 1, 0));
    for (int i = 1; i <= a.length(); i++) {
        dp[i][0] = dp[i - 1][0];
        if (c[i - 1] == a[i - 1]) dp[i][0]++;
    }

    for (int j = 1; j <= b.length(); j++) {
        dp[0][j] = dp[0][j - 1];
        if (c[j - 1] == b[j - 1]) dp[0][j]++;
    }

    for (int i = 1; i <= a.length(); i++) {
        for (int j = 1; j <= b.length(); j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

            if (c[i + j - 1] == a[i - 1]) dp[i][j] = max(dp[i][j], dp[i - 1][j] + 1);
            if (c[i + j - 1] == b[j - 1]) dp[i][j] = max(dp[i][j], dp[i][j - 1] + 1);
        }
    }

    cout << c.length() - dp[a.length()][b.length()] << endl;
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
