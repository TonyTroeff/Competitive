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

void init() {
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector votes(n, string(m, ' '));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> votes[i][j];

    vector<int> winning;
    winning.reserve(m);

    for (int j = 0; j < m; j++) {
        int zeros = 0, ones = 0;
        for (int i = 0; i < n; i++) {
            if (votes[i][j] == '0') zeros++;
            else if (votes[i][j] == '1') ones++;
        }

        winning.push_back(zeros == 0 || ones > zeros);
    }

    int min = m;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        int wins = 0;
        for (int j = 0; j < m; j++)
            wins += '0' + winning[j] == votes[i][j];

        if (wins < min) {
            min = wins;
            ans.clear();
        }

        if (wins == min)
            ans.push_back(i + 1);
    }

    for (const int &el: ans) cout << el << ' ';
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();
    solve();
}
