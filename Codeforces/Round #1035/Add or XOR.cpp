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

int solve(const int& a, const int& b, const int& x, const int& y) {
    if (a == b) return 0;
    if (a == b + 1 && a % 2 != 0) return y;

    if (a < b) {
        const int diff = b - a, half_diff = diff / 2;
        int c1 = half_diff, c2 = half_diff;

        if (diff % 2 != 0) {
            if (a % 2 != 0) c1++;
            else c2++;
        }

        return c1 * x + c2 * min(x, y);
    }

    return -1;
}

void solve() {
    int a, b, x, y;
    cin >> a >> b >> x >> y;



    cout << solve(a,b,x,y) << endl;
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
