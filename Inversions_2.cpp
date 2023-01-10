#include <bits/stdc++.h>
#define int long long int

using namespace std;

class Segment_Tree
{
private:
    vector<int> seg_tree;
    int arr_size;

    void buildUtil(int low, int high, int seg_index)
    {
        if (low == high)
        {
            seg_tree[seg_index] = 1;
            return;
        }

        int mid = low + (high - low) / 2;
        buildUtil(low, mid, 2 * seg_index + 1);
        buildUtil(mid + 1, high, 2 * seg_index + 2);
        seg_tree[seg_index] = seg_tree[2 * seg_index + 1] + seg_tree[2 * seg_index + 2];
    }

    void removeUtil(int low, int high, int seg_index, int value)
    {
        if (low == high)
        {
            seg_tree[seg_index] = 0;
            return;
        }

        int mid = low + (high - low) / 2;
        if (value >= low && value <= mid)
            removeUtil(low, mid, 2 * seg_index + 1, value);
        else
            removeUtil(mid + 1, high, 2 * seg_index + 2, value);
        seg_tree[seg_index] = seg_tree[2 * seg_index + 1] + seg_tree[2 * seg_index + 2];
    }

    int queryUtil(int low, int high, int seg_index, int k)
    {
        if (low == high)
        {
            return low;
        }

        int mid = low + (high - low) / 2;
        if (seg_tree[2 * seg_index + 2] >= k)
            return queryUtil(mid + 1, high, 2 * seg_index + 2, k);
        return queryUtil(low, mid, 2 * seg_index + 1, k - seg_tree[2 * seg_index + 2]);
    }

public:
    Segment_Tree(const int size)
    {
        build(size);
    }

    void build(int size)
    {
        arr_size = size;
        seg_tree.resize(1 << signed(ceil(log2(arr_size)) + 1));
        buildUtil(0, arr_size - 1, 0);
    }

    void remove(int value)
    {
        removeUtil(0, arr_size - 1, 0, value);
    }

    int query(int k)
    {
        return queryUtil(0, arr_size - 1, 0, k);
    }
};

signed main(void)
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    Segment_Tree st(n);
    vector<int> answer(n);

    for (int i = n - 1; i >= 0; i--)
    {
        answer[i] = st.query(arr[i] + 1) + 1;
        st.remove(answer[i] - 1);
    }

    for (auto &&element : answer)
    {
        cout << element << ' ';
    }
    cout << '\n';
    return 0;
}