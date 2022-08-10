#include <bits/stdc++.h>
#define FASTIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr);

using namespace std;

int main(void)
{
    // FASTIO
    int t, numberOfNodes, d12, d23, d13;
    cin >> t;
    while (t--)
    {
        cin >> numberOfNodes >> d12 >> d23 >> d13;
        int _numberOfNodes = numberOfNodes;

        int h = (d13 - d23 + d12);
        int x = (d13 + d23 - d12);

        if ((h & 1) || (h < 0) || (x & 1) || (x < 0))
        {
            cout << "NO\n";
            continue;
        }

        h /= 2;
        x /= 2;
        bool possible = true;
        vector<vector<int>> tree(_numberOfNodes + 1);
        int depthOf2 = d12, depthOf3 = h + x, node = 1;
        int _depthOf2 = depthOf2, _depthOf3 = depthOf3;
        if (depthOf2 < depthOf3)
        {
            // Fixing position of 2
            while (depthOf2 != 1)
            {
                if (numberOfNodes <= 3)
                {
                    possible = false;
                    break;
                }
                tree[node].push_back(numberOfNodes);
                node = numberOfNodes;
                numberOfNodes--;
                depthOf2--;
            }

            if (!possible)
            {
                cout << "NO\n";
                continue;
            }

            tree[node].push_back(2);

            if (h > _depthOf2)
            {
                cout << "NO\n";
                continue;
            }
            // Fixing position of 3
            node = 1;
            for (int i = 0; i < h; i++)
            {
                node = tree[node].front();
            }

            while (x != 1)
            {
                if (numberOfNodes <= 3)
                {
                    possible = false;
                    break;
                }

                tree[node].push_back(numberOfNodes);
                node = numberOfNodes;
                numberOfNodes--;
                x--;
            }

            if (!possible)
            {
                cout << "NO\n";
                continue;
            }

            tree[node].push_back(3);

            // Fixing rest of the nodes
            while (numberOfNodes > 3)
            {
                tree[1].push_back(numberOfNodes);
                numberOfNodes--;
            }
        }
        else
        {
            // Fixing position of 3
            while (depthOf3 != 1)
            {
                if (numberOfNodes <= 3)
                {
                    possible = false;
                    break;
                }
                tree[node].push_back(numberOfNodes);
                node = numberOfNodes;
                numberOfNodes--;
                depthOf3--;
            }

            if (!possible)
            {
                cout << "NO\n";
                continue;
            }

            tree[node].push_back(3);

            if (h > _depthOf3)
            {
                cout << "NO\n";
                continue;
            }

            // Fixing position of 2
            node = 1;
            for (int i = 0; i < h; i++)
            {
                node = tree[node].front();
            }

            x = d12 - h;
            while (x != 1)
            {
                if (numberOfNodes <= 3)
                {
                    possible = false;
                    break;
                }

                tree[node].push_back(numberOfNodes);
                node = numberOfNodes;
                numberOfNodes--;
                x--;
            }

            if (!possible)
            {
                cout << "NO\n";
                continue;
            }

            tree[node].push_back(2);

            // Fixing rest of the nodes
            while (numberOfNodes > 3)
            {
                tree[1].push_back(numberOfNodes);
                numberOfNodes--;
            }
        }

        cout << "YES\n";
        for (int i = 1; i <= _numberOfNodes; i++)
        {
            for (auto &&ngbr : tree[i])
            {
                cout << i << ' ' << ngbr << '\n';
            }
        }
    }
    return 0;
}