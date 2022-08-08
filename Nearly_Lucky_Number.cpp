#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    unsigned long long int num;
    cin >> num;
    int luckyDigits = 0;
    while (num)
    {
        if (num % 10 == 4 || num % 10 == 7)
            luckyDigits++;
        num /= 10;
    }

    bool lucky = false;
    while (luckyDigits)
    {
        lucky = true;
        if (luckyDigits % 10 != 4 && luckyDigits % 10 != 7)
        {
            lucky = false;
            break;
        }
        luckyDigits /= 10;
    }

    if (lucky)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}