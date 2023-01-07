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
        seg_tree[seg_index] = seg_tree[2 * seg_index + 1] + seg_tree[2 * seg_index + 2];
    }

    int queryUtil(int low, int high, int seg_index, int start, int end)
    {
        if (start <= low && end >= high)
        {
            return seg_tree[seg_index];
        }

        if (start > high || end < low)
        {
            return 0;
        }

        int mid = low + (high - low) / 2;
        int left = queryUtil(low, mid, 2 * seg_index + 1, start, end);
        int right = queryUtil(mid + 1, high, 2 * seg_index + 2, start, end);
        return left + right;
    }

public:
    Segment_Tree(vector<int> const &arr)
    {
        build(arr);
    }

    void build(vector<int> const &arr)
    {
        arr_size = arr.size();
        seg_tree.resize(4 * arr_size + 1);
        buildUtil(0, arr_size - 1, 0, arr);
    }

    void update(int index, int value)
    {
        updateUtil(0, arr_size - 1, 0, index, value);
    }

    int query(int start, int end)
    {
        return queryUtil(0, arr_size - 1, 0, start, end);
    }
};

signed main(void)
{
    int n, m, q, v1, v2;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    Segment_Tree st(arr);
    for (int i = 0; i < m; i++)
    {
        cin >> q >> v1 >> v2;
        switch (q)
        {
        case 1:
            st.update(v1, v2);
            break;
        case 2:
            cout << st.query(v1, v2 - 1) << '\n';
            break;
        }
    }
    return 0;
}