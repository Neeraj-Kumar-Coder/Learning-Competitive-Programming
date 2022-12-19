#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int main(void)
{
    ll t;
    cin >> t;

    while (t--)
    {
        ll n;
        cin >> n;
        vector<ll> arr(n);
        for (size_t i = 0; i < n; i++)
            cin >> arr[i];

        ll mean = 0;
        for (size_t i = 0; i < n - 1; i++)
            if (arr[i] > arr[i + 1] && mean < ceill((arr[i] + arr[i + 1]) / 2.0))
                mean = ceill((arr[i] + arr[i + 1]) / 2.0);

        bool sorted = true;
        for (size_t i = 0; i < n - 1; i++)
        {
            if (llabs(arr[i] - mean) > llabs(arr[i + 1] - mean))
            {
                sorted = false;
                break;
            }
        }
        if (sorted)
            cout << mean << '\n';
        else
            cout << -1 << '\n';
    }
    return 0;
}