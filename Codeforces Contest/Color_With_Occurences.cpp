#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int q, n;
    cin >> q;
    string str;

    while (q--)
    {
        cin >> str;
        cin >> n;
        vector<string> word(n);
        for (int i = 0; i < n; i++)
        {
            cin >> word[i];
        }

        vector<pair<int, int>> dist(str.length(), {0, 0});
        for (int i = 0; i < str.length(); i++)
        {
            for (int j = 0; j < n; j++)
            {
                int it;
                for (it = 0; i + it < str.length() && it < word[j].length(); it++)
                {
                    if (word[j][it] != str[i + it])
                        break;
                }

                if (it == word[j].length())
                    dist[i] = max(dist[i], {int(word[j].length()), j + 1});
            }
        }

        vector<pair<int, int>> answer;
        int limit = 0, curlim = 0;
        pair<int, int> used;
        bool flag = true;
        for (int i = 0; i < str.length(); i++)
        {
            if (i == limit)
            {
                if (curlim > dist[i].first + i)
                {
                    answer.push_back(used);
                    limit = curlim;
                }
                else if (dist[i].first + i > i)
                {
                    answer.push_back({dist[i].second, i + 1});
                    limit = dist[i].first + i;
                }
                else
                {
                    flag = false;
                    break;
                }
            }

            if (dist[i].first + i > curlim)
            {
                curlim = dist[i].first + i;
                used = {dist[i].second, i + 1};
            }
        }

        if (!flag)
        {
            cout << -1 << '\n';
            continue;
        }

        cout << answer.size() << '\n';
        for (auto &&p : answer)
        {
            cout << p.first << ' ' << p.second << '\n';
        }
    }
    return 0;
}