

    for (auto &&i : suffixArray)
    {
        for (int j = i; j < str.length(); j++)
        {
            cout << (str[j] - 'a') << ' ';
        }
        cout << '\n';
    }