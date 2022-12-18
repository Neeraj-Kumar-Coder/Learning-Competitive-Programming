#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t, n;
    cin >> t;

    vector<bool> is_prime(1001, true);
    is_prime[0] = is_prime[1] = false;

    for (ll i = 2; i * i <= 1000; i++)
    {
        if (is_prime[i])
        {
            for (ll j = i * i; j <= 1000; j += i)
                is_prime[j] = false;
        }
    }

    for (ll i = 0; i < t; i++)
    {
        cin >> n;
        vector<ll> arr(n);
        vector<ll> hash(1001, -1);
        ll answer = -1;

        for (ll j = 0; j < n; j++)
        {
            cin >> arr[j];

            ll facmul = 1;
            for (ll k = 2; k * k <= arr[j]; k++)
            {
                if (is_prime[k] && arr[j] % k == 0)
                {
                    facmul *= k;
                    while (arr[j] % k == 0)
                    {
                        arr[j] /= k;
                    }
                }
            }
            if (is_prime[arr[j]])
                facmul *= arr[j];

            hash[facmul] = j + 1;
        }

        for (ll a = 0; a < 1001; a++)
        {
            if (hash[a] == -1)
                continue;
            for (ll b = 0; b < 1001; b++)
            {
                if (hash[b] == -1)
                    continue;

                if (gcd(a, b) == 1)
                {
                    answer = max(answer, hash[a] + hash[b]);
                }
            }
        }

        cout << answer << '\n';
    }

    return 0;
}