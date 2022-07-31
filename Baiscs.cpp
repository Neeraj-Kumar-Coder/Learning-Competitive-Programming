#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    // When number of inputs are not known
    int n;
    while (cin >> n)
        cout << "Got the input : " << n << '\n';

    cout << "Input stream ended\n";

    // Compairing floating point numbers (use this method even if '==' operator works)
    double left = 9.343298, right = 9.343298;
    if (abs(left - right) < 1e-9)
        cout << "Both the numbers are equal!\n";
    else
        cout << "Numbers are not equal!\n";
    return 0;
}