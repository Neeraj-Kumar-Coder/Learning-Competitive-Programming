#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    cin >> t;
    while (t--)
    {
        int k, n;
        cin >> k >> n;

        vector<int> res;
        int diff = 1;

        while (n > 0 && res.size() < k)
        {
            res.push_back(n);
            n -= diff;
            diff++;
        }

        if (res.size() < k)
        {
            n = 0;
            int remaining = k - res.size();
            while (remaining > n)
            {
                n = res.back();
                res.pop_back();
                remaining++;
            }
            while (res.size() < k)
            {
                res.push_back(n--);
            }
        }

        reverse(res.begin(), res.end());
        for (auto &&i : res)
        {
            cout << i << ' ';
        }
        cout << '\n';
    }
    return 0;
}