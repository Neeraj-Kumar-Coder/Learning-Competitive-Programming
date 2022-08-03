#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int element;
    vector<int> array;
    cout << "Enter your set (put '.' if input ended): ";
    while (cin >> element)
    {
        array.push_back(element);
    }

    cout << "\nAll subsets of the set are:\n";
    for (size_t it = 0; it < (1ull << array.size()); it++)
    {
        cout << "#" << it + 1 << ": ";
        for (size_t i = 0; i < array.size(); i++)
        {
            if (it & (1ull << i))
                cout << array[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}