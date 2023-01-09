#include <bits/stdc++.h>
#define int long long int

using namespace std;

class Segment_Tree
{
private:
    vector<int> seg_tree;
    int arr_size;

    void buildUtil(int low, int high, int seg_index, vector<int> const &arr)
    {
        if (low == high)
        {
            seg_tree[seg_index] = arr[low];
            return;
        }

        int mid = low + (high - low) / 2;
        buildUtil(low, mid, 2 * seg_index + 1, arr);
        buildUtil(mid + 1, high, 2 * seg_index + 2, arr);
        seg_tree[seg_index] = seg_tree[2 * seg_index + 1] + seg_tree[2 * seg_index + 2];
    }

    void complimentUtil(int low, int high, int seg_index, int index)
    {
        if (low == high)
        {
            seg_tree[seg_index] ^= 1;
            return;
        }

        int mid = low + (high - low) / 2;
        if (index >= low && index <= mid)
            complimentUtil(low, mid, 2 * seg_index + 1, index);
        else
            complimentUtil(mid + 1, high, 2 * seg_index + 2, index);
        seg_tree[seg_index] = seg_tree[2 * seg_index + 1] + seg_tree[2 * seg_index + 2];
    }

    int getIndexOfKthOneUtil(int low, int high, int seg_index, int k)
    {
        if (low == high)
            return low;

        int mid = low + (high - low) / 2;

        if (seg_tree[2 * seg_index + 1] >= k)
            return getIndexOfKthOneUtil(low, mid, 2 * seg_index + 1, k);
        return getIndexOfKthOneUtil(mid + 1, high, 2 * seg_index + 2, k - seg_tree[2 * seg_index + 1]);
    }

public:
    Segment_Tree(vector<int> const &arr)
    {
        build(arr);
    }

    void build(vector<int> const &arr)
    {
        arr_size = arr.size();
        seg_tree.resize(1 << signed((ceil(log2(arr_size)) + 1)));
        buildUtil(0, arr_size - 1, 0, arr);
    }

    void compliment(int index)
    {
        complimentUtil(0, arr_size - 1, 0, index);
    }

    int getIndexOfKthOne(int k)
    {
        return getIndexOfKthOneUtil(0, arr_size - 1, 0, k);
    }
};

signed main(void)
{
    int n, m, q, v;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    Segment_Tree st(arr);
    for (int i = 0; i < m; i++)
    {
        cin >> q >> v;
        switch (q)
        {
        case 1:
            st.compliment(v);
            break;
        case 2:
            cout << st.getIndexOfKthOne(v + 1) << '\n';
            break;
        }
    }

    return 0;
}