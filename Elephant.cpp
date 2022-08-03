#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int x, count = 0;
    cin >> x;
    while (x)
    {
        if (x >= 5)
        {
            count += x / 5;
            x %= 5;
        }
        else if (x >= 4)
        {
            count += x / 4;
            x %= 4;
        }
        else if (x >= 3)
        {
            count += x / 3;
            x %= 3;
        }
        else if (x >= 2)
        {
            count += x / 2;
            x %= 2;
        }
        else if (x >= 1)
        {
            count += x / 1;
            x %= 1;
        }
    }

    cout << count << '\n';
    return 0;
}