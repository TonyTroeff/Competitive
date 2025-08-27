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
#define MAX_P 20

// #define SINGLE_TEST

vector<ll> powers_of_3(MAX_P + 1), costs(MAX_P);

void init() {
    powers_of_3[0] = 1;
    for (int i = 1; i <= MAX_P; i++) powers_of_3[i] = powers_of_3[i - 1] * 3;

    costs[0] = 3;
    for (int i = 1; i < MAX_P; i++) costs[i] = powers_of_3[i + 1] + i * powers_of_3[i - 1];
}

void solve() {
    ll n;
    int k;
    cin >> n >> k;

    vector<int> count(MAX_P);
    int pos = MAX_P - 1;
    while (n > 0) {
        if (powers_of_3[pos] > n) pos--;
        else {
            count[pos]++;
            n -= powers_of_3[pos];
            k--;
        }
    }

    ll ans;
    if (k < 0) ans = -1;
    else {
        ans = 0;
        pos = MAX_P - 1;

        int remaining_ops = k / 2;
        while (pos > 0 && remaining_ops > 0) {
            if (count[pos] == 0) pos--;
            else {
                const int take = min(count[pos], remaining_ops);

                count[pos] -= take;
                count[pos - 1] += take * 3;
                remaining_ops -= take;
            }
        }

        for (int i = 0; i < MAX_P; i++) ans += costs[i] * count[i];
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
