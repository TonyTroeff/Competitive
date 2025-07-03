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
#define MAX 1e5
#define UNKNOWN (-1)

// #define SINGLE_TEST

vector<int> primes;

void generate_primes() {
    vector is_prime(MAX + 1, true);
    for (int p = 2; p * p <= MAX; p++) {
        if (!is_prime[p]) continue;

        for (int i = p * p; i <= MAX; i += p)
            is_prime[i] = false;
    }

    for (int p = 2; p <= MAX; p++)
        if (is_prime[p]) primes.push_back(p);
}

void init() {
    generate_primes();
}

void solve() {
    int n;
    cin >> n;

    vector p(n, UNKNOWN);
    p[0] = 1;

    const int max_prime_index = static_cast<int>(distance(primes.begin(), ranges::upper_bound(primes, n))) - 1;
    for (int i = max_prime_index; i >= 0; i--) {
        const int current_prime = primes[i];
        int prev_val = current_prime, val = 2 * current_prime;
        while (val <= n) {
            if (p[val - 1] == UNKNOWN) {
                p[val - 1] = prev_val;

                prev_val = val;
            }

            val += current_prime;
        }

        p[current_prime - 1] = prev_val;
    }

    for (int i = 0; i < n; i++)
        cout << p[i] << ' ';
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
