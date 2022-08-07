#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    string word;
    cin >> word;
    int upper = 0, lower = 0;
    for (auto &&ch : word)
    {
        if (isupper(ch))
            upper++;
        else
            lower++;
    }

    if (lower >= upper)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
    }
    else
    {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
    }

    cout << word << '\n';
    return 0;
}