#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int freq[26] = {0};
    string s;
    cin >> s;
    int sizeOfSet = 0;
    for (auto &&ch : s)
    {
        if (freq[ch - 'a']++ == 0)
        {
            sizeOfSet++;
        }
    }

    if (sizeOfSet & 1)
        cout << "IGNORE HIM!\n";
    else
        cout << "CHAT WITH HER!\n";
    return 0;
}