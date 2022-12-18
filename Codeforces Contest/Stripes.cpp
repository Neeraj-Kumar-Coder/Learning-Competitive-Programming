#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    char mat[8][8];
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                cin >> mat[j][k];
            }
        }

        bool flag = false;
        for (int j = 0; j < 8; j++)
        {
            if (mat[j][0] == '.')
                continue;

            int b = 0, r = 0;
            for (int k = 0; k < 8; k++)
            {
                if (mat[j][k] == 'R')
                    r++;
            }
            if (r == 8)
            {
                flag = true;
                cout << "R\n";
            }

            if (flag)
                break;
        }
        if (flag)
            continue;

        for (int j = 0; j < 8; j++)
        {
            if (mat[0][j] == '.')
                continue;

            int b = 0, r = 0;
            for (int k = 0; k < 8; k++)
            {
                if (mat[k][j] == 'B')
                    b++;
            }

            if (b == 8)
            {
                flag = true;
                cout << "B\n";
            }

            if (flag)
                break;
        }
        if (flag)
            continue;
    }

    return 0;
}