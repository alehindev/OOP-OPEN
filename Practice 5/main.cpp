#include <iostream>
#include <bits/stdc++.h>

using namespace std;


template <class T>

class BaseMatrix
{
protected:
    T **ptr;
    int height;
    int width;

    double Scalar(double *arr1, double *arr2, int len)
    {
        double res = 0;
        for (int i = 0; i < len; i++)
        {
            res += arr1[i] * arr2[i];
        }
        return res;
    }

public:
    BaseMatrix(int Height = 2, int Width = 2) // constructor
    {
        height = Height;
        width = Width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
            ptr[i] = new double[width];
    }

    BaseMatrix(const BaseMatrix &M) //constructor of copy
    {
        height = M.height;
        width = M.width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
            ptr[i] = new double[width];

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ptr[i][j] = M.ptr[i][j];
            }
        }
    }

    ~BaseMatrix() // destructor
    {
        if (ptr != NULL)
        {
            for (int i = 0; i < height; i++)
                delete[] ptr[i];
            delete[] ptr;
            ptr = NULL;
        }
    }

    void print()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
                cout << ptr[i][j] << " ";
            cout << "\n";
        }
    }
    double &operator()(int row, int column)
    {
        return ptr[row][column];
    }

    BaseMatrix trans()
    {
        BaseMatrix Res(width, height);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Res(j, i) = ptr[i][j];
            }
        }

        return Res;
    }
    double *operator*(double *arr)
    {
        double *res = new double[height];
        for (int i = 0; i < height; i++)
        {
            res[i] = Scalar(ptr[i], arr, width);
        }
        return res;
    }
};

int main()
{
    BaseMatrix M(2, 3);
    double vec[]= {}
    // написать умножение матриц и написать 
    M.trans();
    M.print();

    return 0;
}
