#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int a[110][110];

int main()
{
    int n, m;
    int cl, fr, bh;
    bool Bcl, Bfr, Bbh;

    Bcl = Bfr = Bbh = true;
    cl = fr = bh = 0;

    cout << "Введите размер матрицы:" << endl;
    cout << "N: ";
    cin >> n;
    cout << "M: ";
    cin >> m;
    cout << "Введите матрицу:" << endl;

    //считываем матрицу
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }
    //обрабатываем матрицу
    for (int j = 0; j < m; j++){
        for (int i = 0; i < n; i++)
        {
            if (a[i][j] == 0) {
                if (Bcl){
                    
                }
            }
        }
    }
}