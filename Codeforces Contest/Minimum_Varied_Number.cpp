#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int current = 9;
        string answer;
        while (n)
        {
            if (n < current)
            {
                answer.append(to_string(n));
                n = 0;
            }
            else
            {
                answer.append(to_string(current));
                n -= current;
                current--;
            }
        }
        reverse(answer.begin(), answer.end());
        cout << answer << '\n';
    }
    return 0;
}