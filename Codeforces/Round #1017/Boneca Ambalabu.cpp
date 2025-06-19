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

#define BIT_LEN 30

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    vector<int> bits_count(BIT_LEN);
    for (const int &el: a) {
        for (int m = 1, j = 0; j < BIT_LEN; m <<= 1, j++) {
            if ((el & m) != 0) bits_count[j]++;
        }
    }

    ll ans = 0;
    for (const int &el: a) {
        ll sum = 0, m = 1;
        for (int j = 0; j < BIT_LEN; m <<= 1, j++) {
            if ((el & m) == 0) sum += m * bits_count[j];
            else sum += m * (n - bits_count[j]);
        }

        ans = max(ans, sum);
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
