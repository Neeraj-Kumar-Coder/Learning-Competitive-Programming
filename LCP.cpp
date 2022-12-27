#include <bits/stdc++.h>

using namespace std;

void radix_sort(vector<pair<pair<int, int>, int>> &arr)
{
    int n = arr.size();
    vector<int> cnt(n, 0);
    vector<pair<pair<int, int>, int>> temp(n);

    for (auto &&p : arr)
        cnt[p.first.second]++;

    for (int i = 1; i < n; i++)
        cnt[i] += cnt[i - 1];

    for (int i = 0; i < n; i++)
        temp[--cnt[arr[i].first.second]] = arr[i];

    fill(cnt.begin(), cnt.end(), 0);

    for (auto &&p : temp)
        cnt[p.first.first]++;

    for (int i = 1; i < n; i++)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; i--)
        arr[--cnt[temp[i].first.first]] = temp[i];
}

vector<int> getSuffixArrayInNLOGN(string &str)
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
            c[p[i]] = c[p[i - 1]] + (str[p[i]] == str[p[i - 1]] ? 0 : 1);
    }

    // k = k + 1
    for (int k = 0; (1 << k) < n; k++)
    {
        vector<pair<pair<int, int>, int>> temp;
        for (int i = 0; i < n; i++)
            temp.emplace_back(make_pair(c[i], c[(i + (1 << k)) % n]), i);

        radix_sort(temp);

        for (int i = 0; i < n; i++)
            p[i] = temp[i].second;

        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
            c[p[i]] = c[p[i - 1]] + (temp[i].first == temp[i - 1].first ? 0 : 1);
    }
    str.pop_back();
    return p;
}

vector<int> LPS(const string &str, vector<int> &suffixArray)
{
    vector<int> lps(str.length());
    int k = 0;

    vector<int> mp(str.size() + 1);
    for (int i = 0; i < suffixArray.size(); i++)
        mp[suffixArray[i]] = i;

    for (int i = 0; i < str.length(); i++)
    {
        int pi = mp[i];
        if (pi == suffixArray.size() - 1)
            continue;

        int j = suffixArray[pi + 1];
        while (i + k < str.length() && j + k < str.length() && str[i + k] == str[j + k])
            k++;

        lps[pi] = k;
        k = max(0, k - 1);
    }
    return lps;
}

int main(void)
{
    string str;
    cin >> str;

    vector<int> suffixArray = getSuffixArrayInNLOGN(str);
    vector<int> lps = LPS(str, suffixArray);

    for (auto &&index : suffixArray)
        cout << index << ' ';
    cout << '\n';
    for (auto &&len : lps)
        cout << len << ' ';

    return 0;
}