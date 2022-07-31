#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n, k, value, kth = -1, i;
    cin >> n >> k;
    for (i = 0; i < n; i++)
    {
        cin >> value;
        if (--k == 0)
            kth = value;
        if (value == 0 || (kth != -1 && value != kth))
            break;
    }
    cout << i << '\n';
    return 0;
}