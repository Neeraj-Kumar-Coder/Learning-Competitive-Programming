#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n, solved = 0;
    cin >> n;
    while (n--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a + b + c >= 2)
            solved++;
    }
    cout << solved << '\n';
    return 0;
}