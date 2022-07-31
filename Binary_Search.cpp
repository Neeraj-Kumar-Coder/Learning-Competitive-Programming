#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int element;
    cin >> element;
    auto pointer = equal_range(arr.begin(), arr.end(), element);

    cout << "Count = " << pointer.second - pointer.first << '\n';
    return 0;
}