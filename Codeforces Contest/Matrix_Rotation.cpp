#include <bits/stdc++.h>

using namespace std;

bool beautiful(int a, int b, int c, int d)
{
    return a < b && c < d && a < c && b < d;
}

int main(void)
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        for (short i = 0; i < 3 && !beautiful(a, b, c, d); i++)
        {
            int ta = a;
            a = c;
            c = d;
            d = b;
            b = ta;
        }

        if (beautiful(a, b, c, d))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}