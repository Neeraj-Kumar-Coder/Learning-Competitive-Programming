#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    bitset<100> bs;
    bs.set(0);
    bs.set(99);
    cout << bs << '\n';
    cout << bs.count() << '\n';

    bitset<10> b1(string("1001010010")), b2(string("0100111100"));
    cout << b1 << '\n';
    cout << b2 << '\n';
    cout << (b1 & b2) << '\n';
    cout << (b1 | b2) << '\n';
    cout << (b1 ^ b2) << '\n';
    return 0;
}