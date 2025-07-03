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
#define MAX_CHARACTERS 26

// #define SINGLE_TEST

void init() {
}

void solve() {
    int q;
    cin >> q;

    vector s(MAX_CHARACTERS, 0LL), t(MAX_CHARACTERS, 0LL);
    s[0] = 1;
    t[0] = 1;

    for (int i = 0; i < q; i++) {
        int op, k;
        string x;
        cin >> op >> k >> x;

        for (int j = 0; j < x.length(); j++) {
            if (op == 1) s[x[j] - 'a'] += k;
            else if (op == 2) t[x[j] - 'a'] += k;
        }

        bool ok = false;
        for (int j = 1; !ok && j < MAX_CHARACTERS; j++) {
            if (t[j] > 0) ok = true;
        }

        if (!ok) {
            ok = s[0] < t[0];

            for (int j = 1; ok && j < MAX_CHARACTERS; j++) {
                if (s[j] > 0) ok = false;
            }
        }

        cout << (ok ? "YES" : "NO") << endl;
    }
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
