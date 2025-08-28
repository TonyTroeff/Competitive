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

struct step {
    int row, col, state;
};

vector directions{0, 1, 0, -1, 0};

void init() {
}

void solve() {
    int h, w;
    cin >> h >> w;

    vector grid(h, string(w, ' '));
    int start_row = -1, start_col = -1;
    int goal_row = -1, goal_col = -1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'S') start_row = i, start_col = j;
            else if (grid[i][j] == 'G') goal_row = i, goal_col = j;
        }
    }

    vector memo(h, vector(w, vector(2, false)));
    queue<step> q;
    q.emplace(start_row, start_col, 0);
    memo[start_row][start_col][0] = true;

    bool found = false;
    int iter = 0;
    while (!found && !q.empty()) {
        const int size = static_cast<int>(q.size());
        for (int i = 0; i < size; i++) {
            auto [row, col, state] = q.front();
            q.pop();

            if (grid[row][col] == '?') state = !state;

            for (int j = 1; j <= 4; j++) {
                const int next_row = row + directions[j - 1];
                if (next_row < 0 || next_row >= h) continue;

                const int next_col = col + directions[j];
                if (next_col < 0 || next_col >= w) continue;

                if (memo[next_row][next_col][state] || grid[next_row][next_col] == '#' || (!state && grid[next_row][next_col] == 'x') || (state && grid[next_row][next_col] == 'o')) continue;

                if (next_row == goal_row && next_col == goal_col) {
                    found = true;
                    break;
                }

                memo[next_row][next_col][state] = true;
                q.emplace(next_row, next_col, state);
            }
        }

        iter++;
    }

    cout << (found ? iter : -1) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();
    solve();
}
