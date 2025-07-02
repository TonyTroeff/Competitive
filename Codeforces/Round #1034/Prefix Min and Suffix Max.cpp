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
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    string ans(n, '0');
    ans[0] = ans[n - 1] = '1';

    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[min_index]) {
            min_index = i;
            ans[i] = '1';
        }
    }

    int max_index = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] > a[max_index]) {
            max_index = i;
            ans[i] = '1';
        }
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