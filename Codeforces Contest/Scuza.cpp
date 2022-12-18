#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t, n, q, s;
    cin >> t;
    while (t--)
    {
        cin >> n >> q;
        vector<ll> height(n), maxTillNow(n, 0), prefix(n);
        for (ll i = 0; i < n; i++)
        {
            cin >> height[i];
            maxTillNow[i] = max(height[i], i > 0 ? maxTillNow[i - 1] : 0ll);
            prefix[i] = (i > 0 ? prefix[i - 1] : 0) + height[i];
        }

        for (ll i = 0; i < q; i++)
        {
            cin >> s;

            ll idx = upper_bound(maxTillNow.begin(), maxTillNow.end(), s) - maxTillNow.begin();
            if (idx == 0)
                cout << 0 << ' ';
            else
                cout << prefix[idx - 1] << ' ';
        }
        cout << '\n';
    }
    return 0;
}