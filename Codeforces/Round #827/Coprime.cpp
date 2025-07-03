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
#define MAX 1e4
#define UNKNOWN (-1)

// #define SINGLE_TEST

vector coprime_pairs(MAX + 1, vector<int>());
vector last_pos(MAX + 1, UNKNOWN);

void init() {
    for (int i = 1; i <= MAX; i++) {
        for (int j = i; j <= MAX; j++) {
            if (gcd(i, j) == 1)
                coprime_pairs[i].push_back(j);
        }
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    const int max_el = ranges::max(a);

    for (int i = 0; i < n; i++)
        last_pos[a[i]] = i + 1;

    int ans = -1;
    for (int i = 1; i <= max_el; i++) {
        for (const int &j: coprime_pairs[i]) {
            if (j > max_el) break;

            if (last_pos[i] != UNKNOWN && last_pos[j] != UNKNOWN)
                ans = max(ans, last_pos[i] + last_pos[j]);
        }
    }

    for (const int &el: a)\
        last_pos[el] = UNKNOWN;

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
