#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    assert(n > 0);
    int a, b, inTram = 0, capacity = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        inTram += b - a;
        capacity = max(capacity, inTram);
    }
    cout << capacity << '\n';
    return 0;
}