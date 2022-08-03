#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int element, x, y;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> element;
            if (element)
            {
                x = i;
                y = j;
                goto output;
            }
        }
    }
output:
    int moves = abs(2 - y) + abs(2 - x);
    cout << moves << '\n';
    return 0;
}