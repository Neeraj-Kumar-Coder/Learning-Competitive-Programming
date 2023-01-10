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
            seg_tree[seg_index] = 0;
            return;
        }

        int mid = low + (high - low) / 2;
        buildUtil(low, mid, 2 * seg_index + 1);
        buildUtil(mid + 1, high, 2 * seg_index + 2);
        seg_tree[seg_index] = seg_tree[2 * seg_index + 1] + seg_tree[2 * seg_index + 2];
    }

    void insertUtil(int low, int high, int seg_index, int value)
    {
        if (low == high)
        {
            seg_tree[seg_index] = 1;
            return;
        }

        int mid = low + (high - low) / 2;
        if (value >= low && value <= mid)
            insertUtil(low, mid, 2 * seg_index + 1, value);
        else
            insertUtil(mid + 1, high, 2 * seg_index + 2, value);
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

    void build(int size)
    {
        arr_size = size;
        seg_tree.resize(1 << signed(ceil(log2(arr_size)) + 1));
        buildUtil(0, arr_size - 1, 0);
    }

    void insert(int value)
    {
        insertUtil(0, arr_size - 1, 0, value);
    }

    int query(int start, int end)
    {
        return queryUtil(0, arr_size - 1, 0, start, end);
    }
};

signed main(void)
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> answer(n);
    Segment_Tree st(n + 1);
    for (int i = 0; i < n; i++)
    {
        answer[i] = st.query(arr[i] + 1, n);
        st.insert(arr[i]);
    }

    for (auto &&element : answer)
    {
        cout << element << ' ';
    }
    cout << '\n';
    return 0;
}