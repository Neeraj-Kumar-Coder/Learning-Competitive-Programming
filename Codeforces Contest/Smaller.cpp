#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t, q;
    cin >> t;
    while (t--)
    {
        cin >> q;
        ll s[26] = {0};
        ll t[26] = {0};
        s[0] = t[0] = 1;

        ll sl = 1, tl = 1;
        ll qt, k;
        string x;
        for (ll i = 0; i < q; i++)
        {
            cin >> qt >> k >> x;
            if (qt == 1)
            {
                for (auto &&ch : x)
                {
                    s[ch - 'a'] += k;
                }
                sl += x.length() * k;
            }
            else
            {
                for (auto &&ch : x)
                {
                    t[ch - 'a'] += k;
                }
                tl += x.length() * k;
            }

            char sc, tc;
            ll fs, ft;

            for (ll it = 0; it < 26; it++)
            {
                if (s[it])
                {
                    fs = s[it];
                    sc = it + 'a';
                    break;
                }
            }

            for (ll it = 25; it >= 0; it--)
            {
                if (t[it])
                {
                    ft = t[it];
                    tc = it + 'a';
                    break;
                }
            }

            if (sc < tc)
            {
                cout << "YES\n";
            }
            else if (tc < sc)
            {
                cout << "NO\n";
            }
            else if (fs > ft)
            {
                cout << "NO\n";
            }
            else if (fs < ft)
            {
                cout << (fs == sl ? "YES\n" : "NO\n");
            }
            else
            {
                cout << (tl == ft ? "NO\n" : "YES\n");
            }
        }
    }
    return 0;
}