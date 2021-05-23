#include <bits/stdc++.h>
#include <iostream>

using namespace std;

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

class IndexOutOfBounds : public Exception
{
private:
    int index1;
    int index2;

public:
    IndexOutOfBounds() : Exception("Wrong index")
    {
        index1 = -1;
        index2 = -1;
    }

    IndexOutOfBounds(int i, int j) : Exception("Wrong index")
    {
        index1 = i;
        index2 = j;
    }
    IndexOutOfBounds(const IndexOutOfBounds &e) : Exception("Wrong size")
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
        index1 = e.index1;
        index2 = e.index2;
    }

    virtual void print()
    {
        cout << "Exception: " << str << "; index_1: " << index1 << "; "
             << "; index_2: " << index2 << "; " << what();
    }
};

class BaseMatrix
{
protected:
    double **ptr;
    int height;
    int width;
    double ScalarProduct(double *arr1, double *arr2, int len)
    {
        double res = 0;
        for (int i = 0; i < height; i++)
            res += arr1[i] * arr2[i];
        return res;
    }

public:
    BaseMatrix()
    {
        height = 0;
        width = 0;
    }

    BaseMatrix(int Height, int Width)
    {
        if (Height < 1 && Width < 1)
        {
            throw WrongSizeException(Height, Width);
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

    double &operator()(int row, int column)
    {
        if (row > height || row < 0 || column > width || column < 0)
            throw IndexOutOfBounds(row, column);
        return ptr[row][column];
    }

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
    myMatrix() : BaseMatrix()
    {
        cout << "myMatrix default constructor is working" << endl;
    }

    myMatrix(int Height, int Width) : BaseMatrix(Height, Width)
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
                ptr[i][j] = rand() % 10;
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
    friend ostream &operator<<(ostream &ustream, myMatrix &obj)
    {

        ustream << obj.height << " " << obj.width << '\n';
        for (int i = 0; i < obj.height; i++)
        {
            for (int j = 0; j < obj.width; j++)
            {
                if (j == obj.width - 1)
                {
                    ustream << obj.ptr[i][j];
                }
                else
                {
                    ustream << obj.ptr[i][j] << " ";
                }
            }
            ustream << "\n";
        }
        return ustream;
    }
    friend istream &operator>>(istream &ustream, myMatrix &obj)
    {
        int temp;

        int height, width;

        ustream >> height >> width;

        obj.width = width;
        obj.height = height;
        obj.ptr = new double *[height];
        for (int i = 0; i < height; i++)
            obj.ptr[i] = new double[width];

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ustream >> temp;
                obj.ptr[i][j] = temp;
            }
        }

        return ustream;
    }
};

int main()
{
    BaseMatrix a(2, 2);
    myMatrix b(3, 3);
    myMatrix q(3, 3);
    myMatrix z(4, 5);

    b.randomValues();
    q.randomValues();
    z.randomValues();

    pair<double, double> coor;
    coor = b.getCoorOfWeigth();
    cout << endl
         << coor.first << " " << coor.second << endl
         << endl;

    ofstream fout("test.txt");
    if (fout)
    {
        try
        {
            fout << q;
            fout << b;
            fout << z;
            fout.close();
        }
        catch (...)
        {
            cout << "Exception: failure of writing";
        }
    }
    ifstream fin("test.txt");
    if (fin)
    {
        try
        {

            int h, w, pos;
            h = 0;
            w = 0;
            pos = fin.tellg();
            myMatrix tempMatrix;
            while (fin >> tempMatrix)
            {
                tempMatrix.print();
                cout << '\n';
            }

            fin.close();
        }
        catch (...)
        {
            cout << "Exception: failure of reading\n";
        }
    }

    try
    {
        BaseMatrix a(2, 2);
        a(2, -1) = 123;
    }
    catch (IndexOutOfBounds exc)
    {
        exc.print();
    }
    catch (WrongSizeException exc)
    {
        exc.print();
    }
    catch (...)
    {
        cout << "Something went wrong!" << endl;
    }

    return 0;
}