#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class BaseMatrix
{
protected:
    double **ptr;
    int height;
    int width;

public:
    BaseMatrix(int Height = 2, int Width = 2)
    {
        if (Height < 1 && Width < 1)
        {
            throw indexOutOfBounds();
        }
        height = Height;
        width = Width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
            ptr[i] = new double[width];
    }

    BaseMatrix(const BaseMatrix &M)
    {
        height = M.height;
        width = M.width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
            ptr[i] = new double[width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < height; j++)
                ptr[i][j] = M.ptr[i][j];
    }

    ~BaseMatrix()
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

    double &operator()(int row, int column) { return ptr[row][column]; }

    BaseMatrix Transponse()
    {
        BaseMatrix Res(width, height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                Res.ptr[j][i] = ptr[i][j]; // Res(j,i) = ptr[i][j];

        return Res;
    }
    double *operator*(double *arr)
    {
        double *res = new double[height];
        for (int i = 0; i < height; i++)
            res[i] = ScalarProduct(ptr[i], arr, width);
        return res;
    }
};

class myMatrix : public BaseMatrix
{
public:
    myMatrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width)
    {
        cout << "myMatrix constructor is working" << endl;
    }

    ~myMatrix()
    {
        cout << "myMatrix destructor is working" << endl;
    }
    void randomValues()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ptr[i][j] = (18 * i) % 5 + (64 * j) % 5;
            }
        }
    }
    pair<double, double> getCoorOfWeigth()
    {
        double x, y, divider;
        divider = x = y = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                x += ptr[i][j] * (i + 1);
                y += ptr[i][j] * (j + 1);
                divider += ptr[i][j];
            }
        }
        x /= divider;
        y /= divider;
        return (make_pair(x, y));
    }
};

class Exception : public exception
{
protected:
    //сообщение об ошибке
    char *str;

public:
    Exception(const char *s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    Exception(const Exception &e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }
    ~Exception()
    {
        delete[] str;
    }
    //функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
    virtual void print()
    {
        cout << "Exception: " << str << "; " << what();
    }
};

class WrongSizeException : public Exception
{
protected:
    int height, width;

public:
    WrongSizeException(int H, int W) : Exception("Wrong size")
    {
        height = H, width = W;
    }

    WrongSizeException() : Exception("Wrong size")
    {
        height = 0, width = 0;
    }

    WrongSizeException(const WrongSizeException &e) : Exception("Wrong size")
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
        height = e.height, width = e.width;
    }

    virtual void print()
    {
        cout << "Exception: " << str << "; dimensions of matrix: " << height << ", " << width << "; " << what();
    }
};

class indexOutOfBounds : public Exception
{
public:
    indexOutOfBounds()
};

int main()
{
    BaseMatrix a(2, 2);
    myMatrix b(3, 3);
    pair<double, double> coor;
    b.randomValues();
    coor = b.getCoorOfWeigth();
    cout << coor.first << " " << coor.second << endl;
    b.print();
    return 0;
}