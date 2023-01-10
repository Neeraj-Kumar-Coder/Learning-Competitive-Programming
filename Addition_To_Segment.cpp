#include <bits/stdc++.h>
#define int long long int

using namespace std;

class Segment_Tree
{
private:
    vector<int> seg_tree;
    int arr_size;

    void updateUtil(int low, int high, int seg_index, int index, int value)
    {
        if (low == high)
        {
            seg_tree[seg_index] += value;
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
    Segment_Tree(const int size)
    {
        build(size);
    }

    void build(const int size)
    {
        arr_size = size;
        seg_tree.resize(4 * arr_size + 1, 0);
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
    int n, m, q, l, r, v, i;
    cin >> n >> m;

    Segment_Tree st(n);
    for (int it = 0; it < m; it++)
    {
        cin >> q;
        switch (q)
        {
        case 1:
            cin >> l >> r >> v;
            st.update(l, v);
            if (r < n)
                st.update(r, -v);
            break;
        case 2:
            cin >> i;
            cout << st.query(0, i) << '\n';
            break;
        }
    }
    return 0;
}