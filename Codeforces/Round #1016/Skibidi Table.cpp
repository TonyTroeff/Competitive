#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 30

vector<long long> powers_of_2(2 * MAX_N + 1);

void initialize_powers_of_2() {
    powers_of_2[0] = 1;

    for (int i = 1; i < powers_of_2.size(); i++)
        powers_of_2[i] = powers_of_2[i - 1] * 2;
}

void solve() {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;

        if (s == "->") {
            int x, y;
            cin >> x >> y;

            long long x_high = powers_of_2[n], y_high = powers_of_2[n];
            long long d = powers_of_2[n * 2] - 1;
            for (int j = n - 1; j >= 0; j--) {
                const long long x_mid = x_high - powers_of_2[j], y_mid = y_high - powers_of_2[j];

                const bool go_up = x <= x_mid, go_left = y <= y_mid;
                if (go_up) x_high = x_mid;
                if (go_left) y_high = y_mid;

                int loss_mult;
                if (go_left) {
                    if (go_up) loss_mult = 3;
                    else loss_mult = 1;
                } else {
                    if (go_up) loss_mult = 0;
                    else loss_mult = 2;
                }

                d -= powers_of_2[2 * j] * loss_mult;
            }

            ++d;
            cout << d << endl;
        } else if (s == "<-") {
            long long d;
            cin >> d;
            --d;

            long long x_high = powers_of_2[n], y_high = powers_of_2[n];

            for (int j = n - 1; j >= 0; j--) {
                const int quadrant = d / powers_of_2[2 * j];

                if (quadrant == 0 || quadrant == 3) x_high -= powers_of_2[j];
                if (quadrant == 0 || quadrant == 2) y_high -= powers_of_2[j];

                d = d % powers_of_2[2 * j];
            }

            cout << x_high << ' ' << y_high << endl;
        }
    }
}

int main() {
    initialize_powers_of_2();

    int t;
    cin >> t;

    while (t--)
        solve();
}
