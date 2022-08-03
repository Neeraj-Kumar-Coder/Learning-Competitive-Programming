#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int a, b;
    cin >> a >> b;
    int year = 1;
    while (true)
    {
        a *= 3;
        b *= 2;
        if (a > b)
            break;
        year++;
    }
    cout << year << '\n';

    return 0;
}