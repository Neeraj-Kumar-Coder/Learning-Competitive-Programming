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
            c[p[i]] = c[p[i - 1]] + (str[p[i]] == str[p[i - 1]] ? 0 : 1);
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

int main(void)
{
    string str;
    cin >> str;

    vector<int> suffixArray = getSuffixArray(str);
    for (auto &&index : suffixArray)
        cout << index << ' ';
    cout << '\n';

    vector<int> suffixArrayNew = getSuffixArrayInNLOGN(str);
    for (auto &&index : suffixArrayNew)
        cout << index << ' ';
    cout << '\n';
    return 0;
}