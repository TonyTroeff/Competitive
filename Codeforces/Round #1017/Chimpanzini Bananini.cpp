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

// #define SINGLE_TEST

void init() {
}

void solve() {
    int q;
    cin >> q;

    deque<int> a;

    ll total_sum = 0, active_res = 0, other_res = 0;
    bool forward = true;
    for (int i = 0; i < q; i++) {
        int s;
        cin >> s;

        if (s == 1) {
            int num;
            if (forward) {
                num = a.back();
                a.pop_back();
                a.push_front(num);
            } else {
                num = a.front();
                a.pop_front();
                a.push_back(num);
            }

            const ll diff = total_sum - static_cast<ll>(a.size()) * num;
            active_res += diff;
            other_res -= diff;
        } else if (s == 2) {
            forward = !forward;
            swap(active_res, other_res);
        } else if (s == 3) {
            int k;
            cin >> k;

            if (forward) a.push_back(k);
            else a.push_front(k);

            active_res += static_cast<ll>(a.size()) * k;
            other_res += k + total_sum;
            total_sum += k;
        }

        cout << active_res << endl;
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
