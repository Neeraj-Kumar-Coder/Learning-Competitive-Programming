#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t, n, val;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> n;
        unordered_set<int> s;
        bool flag = true;
        for (int j = 0; j < n; j++)
        {
            cin >> val;
            if (s.empty() || s.find(val) == s.end())
            {
                s.insert(val);
            }
            else
            {
                flag = false;
            }
        }

        cout << (flag ? "YES" : "NO") << '\n';
    }

    return 0;
}