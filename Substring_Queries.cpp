#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int main(void)
{
    ll n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    vector<ll> substrSize(q);
    vector<char> charToCount(q);
    for (int i = 0; i < q; i++)
        cin >> substrSize[i];
    for (int i = 0; i < q; i++)
        cin >> charToCount[i];

    vector<vector<int>> memory(n, vector<int>(26, 0));
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        for (int length = 1; length < n; length++)
        {
            int low = 0, high = 0, count = 0, total = 0;
            while (high < length)
            {
                if (s[high++] == ch)
                    count++;
            }
            total += count;
            while (high < n)
            {
                if (s[low++] == ch)
                    count--;
                if (s[high++] == ch)
                    count++;
                total += count;
            }
            memory[length - 1][ch - 'a'] = total;
        }
    }

    for (int i = 0; i < q; i++)
        cout << memory[substrSize[i] - 1][charToCount[i] - 'a'] << ' ';

    return 0;
}