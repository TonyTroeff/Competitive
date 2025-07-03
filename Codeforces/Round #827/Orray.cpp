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

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    vector used(n, false);
    int accumulated = 0;
    for (int i = 0; i < n; i++) {
        int best = accumulated, best_index = -1;
        for (int j = 0; j < n; j++) {
            if (used[j]) continue;

            const int candidate = a[j] | accumulated;
            if (candidate > best) {
                best = candidate;
                best_index = j;
            }
        }

        if (best == accumulated) break;

        cout << a[best_index] << ' ';
        used[best_index] = true;
        accumulated = best;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) cout << a[i] << ' ';
    }

    cout << endl;
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
