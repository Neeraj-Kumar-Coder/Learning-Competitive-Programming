#include <bits/stdc++.h>
#define int long long int

using namespace std;

class Suffix_Array
{
private:
    string input;
    vector<int> suffixArray;
    vector<int> lcpArray;

    void radix_sort(vector<int> &p, vector<int> &c)
    {
        int n = p.size();
        vector<int> count(n, 0), new_p(n);
        for (int i = 0; i < n; i++)
            count[c[p[i]]]++;
        for (int i = 1; i < n; i++)
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            new_p[--count[c[p[i]]]] = p[i];
        p = new_p;
    }

public:
    Suffix_Array(void) {}

    Suffix_Array(const string &str) { build(str); }

    void build(const string &str) { input = str + "$"; }

    vector<int> getSuffixArray(void)
    {
        if (suffixArray.size())
            return suffixArray;

        int length = input.length();
        vector<int> p(length), c(length);

        // Initialization
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(), [&](const int &left, const int &right)
             { return input[left] < input[right]; });
        c[p[0]] = 0;
        for (int i = 1; i < length; i++)
            c[p[i]] = c[p[i - 1]] + (input[p[i]] == input[p[i - 1]] ? 0 : 1);

        // Sorting every successive subtring of length 2^k
        vector<int> new_c(length);
        for (int k = 0; (1 << k) < length; k++)
        {
            for (int i = 0; i < length; i++)
                p[i] = (p[i] - (1 << k) + length) % length;

            radix_sort(p, c);
            new_c[p[0]] = 0;
            for (int i = 1; i < length; i++)
                new_c[p[i]] = new_c[p[i - 1]] + (c[p[i]] == c[p[i - 1]] && c[(p[i] + (1 << k)) % length] == c[(p[i - 1] + (1 << k)) % length] ? 0 : 1);
            c = new_c;
        }
        return suffixArray = p;
    }

    vector<int> getLCPArray(void)
    {
        if (lcpArray.size())
            return lcpArray;

        int length = input.length(), k = 0;
        vector<int> lcp(length - 1, 0), inverseMap(length);
        if (suffixArray.empty())
            getSuffixArray();

        for (int i = 0; i < length; i++)
            inverseMap[suffixArray[i]] = i;

        for (int i = 0; i < length; i++)
        {
            int pos = inverseMap[i];
            if (pos == length - 1)
                continue;

            int j = suffixArray[pos + 1];
            while (input[i + k] == input[j + k])
                k++;

            lcp[pos] = k;
            k = max(0LL, k - 1);
        }
        return lcpArray = lcp;
    }
};

int getCount(const string &str, vector<int> &suffixArray, const int index, const int length)
{
    int low = 0, high = suffixArray.size() - 1;
    int lowerBound = -1, upperBound = -1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int idx1 = suffixArray[mid], idx2 = index;

        while (idx1 < str.length() && idx2 < index + length && str[idx1] == str[idx2])
        {
            idx1++;
            idx2++;
        }

        if (idx2 == index + length)
        {
            lowerBound = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if (lowerBound == -1)
        return 0;

    low = 0, high = suffixArray.size() - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int idx1 = suffixArray[mid], idx2 = index;

        while (idx1 < str.length() && idx2 < index + length && str[idx1] == str[idx2])
        {
            idx1++;
            idx2++;
        }

        if (idx2 == index + length)
        {
            upperBound = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return upperBound - lowerBound + 1;
}

signed main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        assert(arr[i] >= 1 && arr[i] <= m);
    }

    string str;
    for (auto &&element : arr)
    {
        char ch = 'a' + element;
        str.push_back(ch);
    }

    Suffix_Array sa(str);
    vector<int> suffixArray = sa.getSuffixArray(), lcpArray = sa.getLCPArray();

    int answerIndex = 0, answerLength = str.length(), answerRefrain = str.length();
    vector<int> nsl(lcpArray.size()), nsr(lcpArray.size());
    stack<int> s;
    for (int i = 0; i < lcpArray.size(); i++)
    {
        while (!s.empty() && lcpArray[s.top()] >= lcpArray[i])
            s.pop();
        nsl[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }

    while (!s.empty())
        s.pop();
    for (int i = lcpArray.size() - 1; i >= 0; i--)
    {
        while (!s.empty() && lcpArray[s.top()] >= lcpArray[i])
            s.pop();
        nsr[i] = s.empty() ? lcpArray.size() : s.top();
        s.push(i);
    }

    for (int i = lcpArray.size() - 1; i >= 0; i--)
    {
        if (!lcpArray[i])
            continue;
        int currentCount = nsr[i] - nsl[i];
        int currentRefrain = lcpArray[i] * currentCount;

        if (currentRefrain > answerRefrain)
        {
            answerRefrain = currentRefrain;
            answerIndex = suffixArray[i];
            answerLength = lcpArray[i];
        }
    }

    cout << answerRefrain << '\n'
         << answerLength << '\n';

    for (int i = 0; i < answerLength; i++)
    {
        cout << (str[answerIndex + i] - 'a') << ' ';
    }
    cout << '\n';
    return 0;
}