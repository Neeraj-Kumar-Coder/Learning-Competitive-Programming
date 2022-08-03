#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    string s;
    cin >> s;
    int one = 0, two = 0, three = 0;
    for (int i = 0; i < s.length(); i += 2)
    {
        switch (s[i])
        {
        case '1':
            one++;
            break;
        case '2':
            two++;
            break;
        case '3':
            three++;
            break;
        }
    }

    for (int i = 0; i < s.length(); i++)
    {
        if (i & 1)
            cout << '+';
        else if (one)
        {
            cout << '1';
            one--;
        }
        else if (two)
        {
            cout << '2';
            two--;
        }
        else if (three)
        {
            cout << '3';
            three--;
        }
    }

    return 0;
}