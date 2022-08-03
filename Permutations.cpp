#include <bits/stdc++.h>

#define FASTIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr);

using namespace std;

bool getNextPermutation(vector<int> &array)
{
    int idx = array.size() - 2;
    while (idx >= 0 && array[idx] >= array[idx + 1])
    {
        idx--;
    }

    if (idx == -1)
        return false;

    reverse(array.begin() + idx + 1, array.end());

    int i = upper_bound(array.begin() + idx + 1, array.end(), array[idx]) - array.begin();

    swap(array[idx], array[i]);
    return true;
}

int main(void)
{
    int element;
    vector<int> array;
    cout << "Enter your set (put '.' if input ended): ";
    while (cin >> element)
    {
        array.push_back(element);
    }

    cout << "\nAll permutations of the set are:\n";
    sort(array.begin(), array.end());
    do
    {
        for (auto &&element : array)
        {
            cout << element << ' ';
        }
        cout << '\n';
    } while (getNextPermutation(array));

    return 0;
}