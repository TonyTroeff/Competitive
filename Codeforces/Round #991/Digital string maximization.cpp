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
    string s;
    cin >> s;

    for (int i = 0; i < s.length(); i++) {
        unsigned char best_val = s[i];
        int best_index = i, offset = 1;

        while (i + offset < s.length() && best_val + offset <= '9') {
            unsigned char candidate_val = s[i + offset] - offset;
            if (candidate_val > best_val) {
                best_val = candidate_val;
                best_index = i + offset;
            }

            offset++;
        }

        while (best_index > i) {
            swap(--s[best_index], s[best_index - 1]);
            best_index--;
        }
    }

    cout << s << endl;
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