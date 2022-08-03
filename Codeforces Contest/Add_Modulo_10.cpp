#include <bits/stdc++.h>

#define int long long int

using namespace std;

signed main(void)
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

        sort(arr.begin(), arr.end());
        bool possible = true;

        for (int i = 0; i < n - 1; i++)
        {
            arr[i] = arr[i] + (arr[i] % 10);
            arr[i + 1] = arr[i + 1] + (arr[i + 1] % 10);
            if (arr[i] != arr[i + 1])
            {
                if (arr[i] % 10 == 0 || arr[i + 1] % 10 == 0)
                {
                    possible = false;
                    break;
                }

                int last_digit_1 = arr[i] % 10;
                int last_digit_2 = arr[i + 1] % 10;
                int rest_number_1 = arr[i] / 10;
                int rest_number_2 = arr[i + 1] / 10;

                if (last_digit_1 == last_digit_2)
                {
                    if ((rest_number_2 - rest_number_1) & 1)
                    {
                        possible = false;
                        break;
                    }
                }
                else if (last_digit_1 == 6 || last_digit_2 == 6)
                {
                    if (!((rest_number_2 - rest_number_1) & 1))
                    {
                        possible = false;
                        break;
                    }
                }
                else if ((rest_number_2 - rest_number_1) & 1)
                {
                    possible = false;
                    break;
                }
            }
        }

        if (possible)
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }
    return 0;
}