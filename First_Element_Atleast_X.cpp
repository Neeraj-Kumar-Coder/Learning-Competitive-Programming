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
        seg_tree[seg_index] = max(seg_tree[2 * seg_index + 1], seg_tree[2 * seg_index + 2]);
    }

    void updateUtil(int low, int high, int seg_index, int index, int value)
    {
        if (low == high)
        {
            seg_tree[seg_index] = value;
            return;
        }

        int mid = low + (high - low) / 2;
        if (index >= low && index <= mid)
            updateUtil(low, mid, 2 * seg_index + 1, index, value);
        else
            updateUtil(mid + 1, high, 2 * seg_index + 2, index, value);
        seg_tree[seg_index] = max(seg_tree[2 * seg_index + 1], seg_tree[2 * seg_index + 2]);
    }

    int queryUtil(int low, int high, int seg_index, int value)
    {
        if (low == high)
            return seg_tree[seg_index] >= value ? low : -1;

        int mid = low + (high - low) / 2;
        if (seg_tree[2 * seg_index + 1] >= value)
            return queryUtil(low, mid, 2 * seg_index + 1, value);
        if (seg_tree[2 * seg_index + 2] >= value)
            return queryUtil(mid + 1, high, 2 * seg_index + 2, value);
        return -1;
    }

public:
    Segment_Tree(vector<int> const &arr)
    {
        build(arr);
    }

    void build(vector<int> const &arr)
    {
        arr_size = arr.size();
        seg_tree.resize(1 << signed(ceil(log2(arr_size)) + 1));
        buildUtil(0, arr_size - 1, 0, arr);
    }

    void update(int index, int value)
    {
        updateUtil(0, arr_size - 1, 0, index, value);
    }

    int query(int value)
    {
        return queryUtil(0, arr_size - 1, 0, value);
    }
};

signed main(void)
{
    int n, m, q, v, i;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    Segment_Tree st(arr);
    for (int it = 0; it < m; it++)
    {
        cin >> q;
        switch (q)
        {
        case 1:
            cin >> i >> v;
            st.update(i, v);
            break;

        case 2:
            cin >> v;
            cout << st.query(v) << '\n';
            break;
        }
    }

    return 0;
}