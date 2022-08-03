#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    string input;
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> input;
        if (input.front() == '+' || input.back() == '+')
            x++;
        else
            x--;
    }
    cout << x << '\n';
    return 0;
}