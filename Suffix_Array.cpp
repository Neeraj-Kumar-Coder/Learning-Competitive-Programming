#include <bits/stdc++.h>

using namespace std;

vector<int> getSuffixArray(string &str)
{
    str += '$';
    int n = str.length();

    vector<int> p(n), c(n);

    // k = 0
    {
        vector<pair<char, int>> temp;
        for (int i = 0; i < n; i++)
            temp.emplace_back(str[i], i);

        sort(temp.begin(), temp.end());
        for (int i = 0; i < n; i++)
            p[i] = temp[i].second;

        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (temp[i].first == temp[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    // k = k + 1
    for (int k = 0; (1 << k) < n; k++)
    {
        vector<pair<pair<int, int>, int>> temp(n);
        for (int i = 0; i < n; i++)
            temp[i] = {{c[i], c[(i + (1 << k)) % n]}, i};

        sort(temp.begin(), temp.end());

        for (int i = 0; i < n; i++)
            p[i] = temp[i].second;

        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (temp[i].first == temp[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    str.pop_back();
    return p;
}

int main(void)
{
    string str;
    cin >> str;

    vector<int> suffixArray = getSuffixArray(str);
    for (auto &&index : suffixArray)
        cout << index << ' ';

    return 0;
}