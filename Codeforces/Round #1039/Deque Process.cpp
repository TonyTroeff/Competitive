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

    vector<int> p(n);
    for (int &el: p) cin >> el;

    string ans(n, ' ');
    int l = 0, r = n - 1;
    for (int i = 0; i < n; i++) {
        bool take_left;
        if (i % 2 == 0) take_left = p[l] < p[r];
        else take_left = p[l] > p[r];

        if (take_left) {
            ans[i] = 'L';
            l++;
        } else {
            ans[i] = 'R';
            r--;
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