#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve(int n, vector<int>& v)
{
    for (int i = 0; i < n; i++) v[i] = (i + 1) * 2;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> v(n);

        solve(n, v);
        for (int j = 0; j < n; j++) cout << v[j] << " ";
        cout << endl;
    }
}