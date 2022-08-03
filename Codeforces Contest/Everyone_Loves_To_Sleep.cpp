#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, H, M, h, m;
        cin >> n >> H >> M;
        vector<int> alarms;
        for (int i = 0; i < n; i++)
        {
            cin >> h >> m;
            alarms.push_back(h * 60 + m);
        }
        sort(alarms.begin(), alarms.end());

        int idx = lower_bound(alarms.begin(), alarms.end(), 60 * H + M) - alarms.begin(), timeSleeped;
        if (idx == n)
        {
            timeSleeped = (24 * 60 - (H * 60 + M)) + alarms.front();
        }
        else
        {
            timeSleeped = alarms[idx] - (60 * H + M);
        }
        cout << timeSleeped / 60 << ' ' << timeSleeped % 60 << '\n';
    }
    return 0;
}