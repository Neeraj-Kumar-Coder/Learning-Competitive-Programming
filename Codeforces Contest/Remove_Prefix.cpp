#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        vector<int> freq(n + 1, 0);
        int i;
        for (i = n - 1; i >= 0; i--)
        {
            if (freq[arr[i]])
                break;
            freq[arr[i]] = 1;
        }
        cout << i + 1 << '\n';
    }
    return 0;
}