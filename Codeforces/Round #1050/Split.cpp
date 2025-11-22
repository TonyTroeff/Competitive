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

ll solve(const int& n, const int& k, const vector<int>& a) {
    if (n % k != 0) return 0;

    optimized_unordered_map<int, int> freq;
    for (const int& el:a) freq[el]++;

    for (int &count: freq | views::values) {
        if (count % k != 0) return 0;
        count /= k;
    }

    optimized_unordered_map<int, int> running;

    int left = 0, right = 0;
    ll ans = 0;
    while (left < n) {
        while (right < n && running[a[right]] < freq[a[right]]) {
            running[a[right]]++;
            right++;
        }

        ans += right - left;

        running[a[left]]--;
        left++;
    }

    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int& el:a) cin >> el;

    cout << solve(n, k, a) << endl;
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