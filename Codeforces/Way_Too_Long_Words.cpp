#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    string str;
    while (n--)
    {
        cin >> str;
        if (str.length() <= 10)
            cout << str << '\n';
        else
            cout << str.front() << (str.length() - 2) << str.back() << '\n';
    }
    return 0;
}