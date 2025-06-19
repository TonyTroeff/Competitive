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
#define UNKNOWN (-1)

// #define SINGLE_TEST

struct trie_node {
    vector<int> next = vector(2, UNKNOWN);
    int last = -1;
};

void init() {
}

int solve(const vector<int> &a, const int k) {
    if (k == 0) return 1;

    vector<trie_node> trie;
    trie.emplace_back();

    int ans = INT_MAX;
    const bitset<BIT_LEN> target(k);

    for (int i = 0; i < a.size(); i++) {
        bitset<BIT_LEN> bits(a[i]);

        int iter_index = 0;
        for (int j = bits.size() - 1; j >= 0; j--) {
            const int current_bit = bits.test(j);

            if (trie[iter_index].next[current_bit] == UNKNOWN) {
                trie[iter_index].next[current_bit] = static_cast<int>(trie.size());
                trie.emplace_back();
            }

            iter_index = trie[iter_index].next[current_bit];
            trie[iter_index].last = i;
        }

        iter_index = 0;
        int best_candidate = UNKNOWN;
        bool can_reach_equality = true;
        for (int j = bits.size() - 1; j >= 0; j--) {
            const int current_bit = bits.test(j), flipped_bit = bits.test(j) ^ 1;
            int continue_with = current_bit;

            if (trie[iter_index].next[flipped_bit] != UNKNOWN) {
                if (target.test(j)) continue_with = flipped_bit;
                else best_candidate = max(best_candidate, trie[trie[iter_index].next[flipped_bit]].last);
            } else {
                if (target.test(j)) {
                    can_reach_equality = false;
                    break;
                }
            }

            iter_index = trie[iter_index].next[continue_with];
            if (iter_index == UNKNOWN) break;
        }

        if (iter_index != UNKNOWN && can_reach_equality)
            best_candidate = max(best_candidate, trie[iter_index].last);

        if (best_candidate != UNKNOWN)
            ans = min(ans, i - best_candidate + 1);
    }

    if (ans == INT_MAX) return -1;
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    cout << solve(a, k) << endl;
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
