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
#define IMPOSSIBLE (-1)

// #define SINGLE_TEST

void init() {
}

void count_values(const int &n, vector<int> &freq) {
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;

        freq[val]++;
    }
}

void build_prefix(const vector<int> &freq, vector<int> &prefix) {
    int index = 0, prefix_sum = 0;
    do {
        prefix[index] = prefix_sum;
        prefix_sum += freq[index] - 1;
    } while (freq[index++] > 0 && index < freq.size());

    while (index < freq.size()) prefix[index++] = IMPOSSIBLE;
}

void build_line(const int& n, const vector<int> &freq, const vector<int>& prefix, vector<int> &line) {
    int suffix_sum = 0;

    for (int i = n; i >= 0; i--) {
        if (prefix[i] != IMPOSSIBLE) {
            line[freq[i]]++;
            line[prefix[i] + freq[i] + suffix_sum + 1]--;
        }

        suffix_sum += freq[i];
    }
}

void solve() {
    int n;
    cin >> n;

    const size_t sz = n + 2;
    vector freq(sz, 0), prefix(sz, 0), line(sz, 0);
    count_values(n, freq);
    build_prefix(freq, prefix);
    build_line(n, freq, prefix, line);

    int total = 0;
    for (int i = 0; i <= n; i++) {
        total += line[i];
        cout << total << ' ';
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
