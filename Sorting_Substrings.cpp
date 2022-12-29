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

    void build(const string &str) { input = str + " "; }

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

class Segment_Tree
{
private:
    vector<int> seg_tree;
    int arr_size;

    void buildUtil(int low, int high, int seg_index, const vector<int> &arr)
    {
        if (low == high)
        {
            seg_tree[seg_index] = arr[low];
            return;
        }

        int mid = low + (high - low) / 2;
        buildUtil(low, mid, 2 * seg_index + 1, arr);
        buildUtil(mid + 1, high, 2 * seg_index + 2, arr);
        seg_tree[seg_index] = min(seg_tree[2 * seg_index + 1], seg_tree[2 * seg_index + 2]);
    }

    int queryUtil(int low, int high, int seg_index, int start, int end)
    {
        if (low >= start && high <= end)
            return seg_tree[seg_index];
        if (low > end || high < start)
            return INT_MAX;

        int mid = low + (high - low) / 2;
        int left = queryUtil(low, mid, 2 * seg_index + 1, start, end);
        int right = queryUtil(mid + 1, high, 2 * seg_index + 2, start, end);
        return min(left, right);
    }

public:
    Segment_Tree(const vector<int> &arr) { build(arr); }

    void build(const vector<int> &arr)
    {
        arr_size = arr.size();
        seg_tree.resize(4 * arr_size + 1);
        buildUtil(0, arr_size - 1, 0, arr);
    }

    int queryMinimumInRange(int low, int high)
    {
        return queryUtil(0, arr_size - 1, 0, low, high);
    }
};

int main(void)
{
    string str;
    int n;
    cin >> str;
    cin >> n;
    vector<pair<int, int>> substring(n);
    for (int i = 0; i < n; i++)
        cin >> substring[i].first >> substring[i].second;

    Suffix_Array sa(str);
    vector<int> suffixArray = sa.getSuffixArray(), lcpArray = sa.getLCPArray();
    vector<int> inverseMap(suffixArray.size());
    for (int i = 0; i < suffixArray.size(); i++)
        inverseMap[suffixArray[i]] = i;
    Segment_Tree st(lcpArray);

    sort(substring.begin(), substring.end(), [&](const pair<int, int> &p1, const pair<int, int> &p2)
         {
        int idx1 = inverseMap[p1.first - 1];
        int idx2 = inverseMap[p2.first - 1];
        int len1 = p1.second - p1.first + 1;
        int len2 = p2.second - p2.first + 1;
        int lcp = str.length() - p1.first + 1;
        if (idx1 != idx2)
            lcp = st.queryMinimumInRange(min(idx1, idx2), max(idx1, idx2) - 1);
        if (len1 > lcp && len2 > lcp)
            return idx1 < idx2;
        if (len1 <= lcp && len2 <= lcp)
            return len1 != len2 ? len1 < len2 : p1 < p2;
        if (len1 <= lcp)
            return true;
        return false; });

    for (auto &&p : substring)
        cout << p.first << ' ' << p.second << '\n';

    return 0;
}