#include <bits/stdc++.h>

using namespace std;

class Suffix_Array
{
private:
    string input;

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

    void build(const string &str) { input = str; }

    vector<int> getSuffixArray(void)
    {
        input += '$';
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
        input.pop_back();
        return p;
    }
};

int main(void)
{
    string str;
    cin >> str;
    Suffix_Array sa(str);
    vector<int> suffixArray = sa.getSuffixArray();
    for (auto &&index : suffixArray)
        cout << index << ' ';
    cout << '\n';
    return 0;
}