#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& el : a) cin >> el;

    ranges::sort(a);

    if (a[0] % 2 == a[n - 1] % 2) return 0;

    int front = 1;
    while (front < n && a[front - 1] % 2 == a[front] % 2) front++;

    int back = 1;
    while (back < n && a[n - back] % 2 == a[n - back - 1] % 2) back++;

    return min(front, back);
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
