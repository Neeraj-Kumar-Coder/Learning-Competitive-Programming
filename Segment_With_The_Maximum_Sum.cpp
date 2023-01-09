#include <bits/stdc++.h>
#define int long long int

using namespace std;

struct Node
{
    int maxSegment;
    int maxPrefix;
    int maxSuffix;
    int totalSum;

    Node(void)
    {
        this->maxSegment = 0;
        this->maxPrefix = 0;
        this->maxSuffix = 0;
        this->totalSum = 0;
    }
    Node(int maxSegment, int maxPrefix, int maxSuffix, int totalSum)
    {
        this->maxSegment = maxSegment;
        this->maxPrefix = maxPrefix;
        this->maxSuffix = maxSuffix;
        this->totalSum = totalSum;
    }
};

class Segment_Tree
{
private:
    vector<Node> seg_tree;
    int arr_size;

    void buildUtil(int low, int high, int seg_index, vector<int> const &arr)
    {
        if (low == high)
        {
            seg_tree[seg_index].totalSum = arr[low];
            seg_tree[seg_index].maxPrefix = max(0LL, arr[low]);
            seg_tree[seg_index].maxSuffix = max(0LL, arr[low]);
            seg_tree[seg_index].maxSegment = max(0LL, arr[low]);
            return;
        }

        int mid = low + (high - low) / 2;
        buildUtil(low, mid, 2 * seg_index + 1, arr);
        buildUtil(mid + 1, high, 2 * seg_index + 2, arr);

        Node left = seg_tree[2 * seg_index + 1];
        Node right = seg_tree[2 * seg_index + 2];

        seg_tree[seg_index].totalSum = left.totalSum + right.totalSum;
        seg_tree[seg_index].maxPrefix = max(left.maxPrefix, left.totalSum + right.maxPrefix);
        seg_tree[seg_index].maxSuffix = max(right.maxSuffix, right.totalSum + left.maxSuffix);
        seg_tree[seg_index].maxSegment = max(max(left.maxSegment, right.maxSegment), left.maxSuffix + right.maxPrefix);
    }

    void updateUtil(int low, int high, int seg_index, int index, int value)
    {
        if (low == high)
        {
            seg_tree[seg_index].totalSum = value;
            seg_tree[seg_index].maxPrefix = max(0LL, value);
            seg_tree[seg_index].maxSuffix = max(0LL, value);
            seg_tree[seg_index].maxSegment = max(0LL, value);
            return;
        }

        int mid = low + (high - low) / 2;
        if (index >= low && index <= mid)
            updateUtil(low, mid, 2 * seg_index + 1, index, value);
        else
            updateUtil(mid + 1, high, 2 * seg_index + 2, index, value);

        Node left = seg_tree[2 * seg_index + 1];
        Node right = seg_tree[2 * seg_index + 2];

        seg_tree[seg_index].totalSum = left.totalSum + right.totalSum;
        seg_tree[seg_index].maxPrefix = max(left.maxPrefix, left.totalSum + right.maxPrefix);
        seg_tree[seg_index].maxSuffix = max(right.maxSuffix, right.totalSum + left.maxSuffix);
        seg_tree[seg_index].maxSegment = max(max(left.maxSegment, right.maxSegment), left.maxSuffix + right.maxPrefix);
    }

    Node queryUtil(int low, int high, int seg_index, int start, int end)
    {
        if (start <= low && end >= high)
        {
            return seg_tree[seg_index];
        }

        if (start > high || end < low)
        {
            return Node(0, 0, 0, 0);
        }

        int mid = low + (high - low) / 2;

        Node left = queryUtil(low, mid, 2 * seg_index + 1, start, end);
        Node right = queryUtil(mid + 1, high, 2 * seg_index + 2, start, end);

        Node result;
        result.totalSum = left.totalSum + right.totalSum;
        result.maxPrefix = max(left.maxPrefix, left.totalSum + right.maxPrefix);
        result.maxSuffix = max(right.maxSuffix, right.totalSum + left.maxSuffix);
        result.maxSegment = max(max(left.maxSegment, right.maxSegment), left.maxSuffix + right.maxPrefix);
        return result;
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

    Node query(int start, int end)
    {
        return queryUtil(0, arr_size - 1, 0, start, end);
    }
};

signed main(void)
{
    int n, m, i, v;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    Segment_Tree st(arr);
    cout << st.query(0, n - 1).maxSegment << '\n';
    for (int it = 0; it < m; it++)
    {
        cin >> i >> v;
        st.update(i, v);
        cout << st.query(0, n - 1).maxSegment << '\n';
    }

    return 0;
}