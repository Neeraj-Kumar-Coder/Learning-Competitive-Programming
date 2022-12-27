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

int countPattern(const string &text, const string &pattern, vector<int> &suffixArray)
{
    int low = 0, high = suffixArray.size() - 1;

    int lowerBound = -1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int i = suffixArray[mid], j = 0;

        while (i < text.length() && j < pattern.length() && text[i] == pattern[j])
        {
            i++;
            ++j;
        }

        if (j == pattern.length())
        {
            lowerBound = mid;
            high = mid - 1;
        }
        else if (i == text.length() || text[i] < pattern[j])
            low = mid + 1;
        else
            high = mid - 1;
    }

    if (lowerBound == -1)
        return 0;

    int upperBound = -1;
    low = 0, high = suffixArray.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int i = suffixArray[mid], j = 0;

        while (i < text.length() && j < pattern.length() && text[i] == pattern[j])
        {
            i++;
            ++j;
        }

        if (j == pattern.length())
        {
            upperBound = mid;
            low = mid + 1;
        }
        else if (i == text.length() || text[i] < pattern[j])
            low = mid + 1;
        else
            high = mid - 1;
    }

    return upperBound - lowerBound + 1;
}

int main(void)
{
    string text, pattern;
    cin >> text;

    vector<int> suffixArray = getSuffixArrayInNLOGN(text);

    int n;
    cin >> n;
    while (n--)
    {
        cin >> pattern;
        cout << countPattern(text, pattern, suffixArray) << '\n';
    }
    return 0;
}