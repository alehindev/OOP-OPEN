#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main()
{
    ofstream fout("test.txt");
    fout << 10 << " " << 20 << '\n';
    fout << 30 << " " << 40 << ' ' << 50 << '\n';
    fout.close();

    ifstream fin("test.txt");
    int pos = fin.tellg();
    int h, w;
    fin >> h >> w;
    fin.seekg(pos, fin.beg);

    return 0;
}