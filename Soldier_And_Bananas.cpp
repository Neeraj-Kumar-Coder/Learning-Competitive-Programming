#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int k, n, w;
    cin >> k >> n >> w;

    int money = k * (w * (w + 1)) / 2;

    cout << max(money - n, 0) << '\n';
    return 0;
}