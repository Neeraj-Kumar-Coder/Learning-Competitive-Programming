#include <bits/stdc++.h>

using namespace std;

int n3sum(vector<int> &arr)
{
    int best = 0, n = arr.size();
    for (int first = 0; first < n; first++)
    {
        for (int last = first; last < n; last++)
        {
            int sum = 0;
            for (int idx = first; idx <= last; idx++)
            {
                sum += arr[idx];
            }
            best = max(best, sum);
        }
    }
    return best;
}

int n2sum(vector<int> &arr)
{
    int best = 0, n = arr.size();
    for (int first = 0; first < n; first++)
    {
        int sum = 0;
        for (int last = first; last < n; last++)
        {
            sum += arr[last];
            best = max(best, sum);
        }
    }
    return best;
}

int n1sum(vector<int> &arr)
{
    int best = 0, sum = 0, n = arr.size();
    for (int current = 0; current < n; current++)
    {
        sum = max(arr[current], sum + arr[current]);
        best = max(best, sum);
    }
    return best;
}

int main(void)
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << n3sum(arr) << '\n';
    cout << n2sum(arr) << '\n';
    cout << n1sum(arr) << '\n';
    return 0;
}