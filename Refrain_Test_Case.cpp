#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    freopen("Refrain_TC.txt", "w", stdout);
    const int n = 1000;
    cout << n << ' ' << 10 << '\n';
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        cout << (count++ % 10 + 1) << ' ';
    }

    return 0;
}