#include <bits/stdc++.h>

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
            k = max(0, k - 1);
        }
        return lcpArray = lcp;
    }
};

int main(void)
{
    string str1, str2;
    cin >> str1 >> str2;

    int n1 = str1.length(), n2 = str2.length();
    string str = str1 + "&" + str2;

    Suffix_Array sa(str);
    vector<int> suffixArray = sa.getSuffixArray();
    vector<int> lcpArray = sa.getLCPArray();
    int answer = 0, index = -1;

    for (int i = suffixArray.size() - 2; i >= 0; i--)
    {
        if ((suffixArray[i] < n1 && suffixArray[i + 1] >= n1) || (suffixArray[i] >= n1 && suffixArray[i + 1] < n1))
        {
            if (lcpArray[i] >= answer)
            {
                answer = lcpArray[i];
                index = suffixArray[i];
            }
        }
    }

    if (answer == 0)
        cout << "" << '\n';
    else
        cout << str.substr(index, answer) << '\n';
    return 0;
}