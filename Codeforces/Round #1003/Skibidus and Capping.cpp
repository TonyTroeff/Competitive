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
#define MAX 2 * 1e5

// #define SINGLE_TEST

vector is_prime(MAX + 1, true);
vector semi_prime_multiples(MAX + 1, make_pair(UNKNOWN, UNKNOWN));

void init() {
    is_prime[0] = is_prime[1] = false;

    vector<int> primes;
    for (int i = 2; i <= MAX; i++) {
        if (!is_prime[i]) continue;

        for (ll j = 1LL * i * i; j <= MAX; j += i)
            is_prime[j] = false;

        primes.push_back(i);
        for (const int &p: primes) {
            const ll semi_prime = 1LL * i * p;
            if (semi_prime > MAX) break;

            semi_prime_multiples[semi_prime] = make_pair(p, i);
        }
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    vector<int> freq(n + 1), additives(n + 1);
    int all_primes_freq = 0;
    ll ans = 0;
    for (const int &el: a) {
        if (is_prime[el]) {
            ans += all_primes_freq - freq[el] + additives[el];
            all_primes_freq++;
        } else {
            const auto &[m1, m2] = semi_prime_multiples[el];
            if (m1 != UNKNOWN && m2 != UNKNOWN) {
                ans += freq[el] + 1;
                ans += freq[m1];
                additives[m1]++;

                if (m1 != m2) {
                    ans += freq[m2];
                    additives[m2]++;
                }
            }
        }

        freq[el]++;
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
