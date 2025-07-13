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
#define DIV 9

// #define SINGLE_TEST

void init() {
}

bool solve(const string &s) {
    int base_sum = 0;
    for (const char &d: s)
        base_sum += d - '0';

    if (base_sum % DIV == 0) return true;

    vector rems(DIV, false);
    rems[base_sum % DIV] = true;

    queue<int> q;
    for (int i = 0; i < s.length(); i++) {
        int inc;
        if (s[i] == '2') inc = 2;
        else if (s[i] == '3') inc = 6;
        else continue;

        for (int j = 0; j < 9; j++) {
            if (rems[j]) q.push((j + inc) % DIV);
        }

        while (!q.empty()) {
            rems[q.front()] = true;
            q.pop();
        }

        if (rems[0]) return true;
    }

    return false;
}

void solve() {
    string s;
    cin >> s;

    cout << (solve(s) ? "YES" : "NO") << endl;
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
