#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Exception : public exception
{
protected:
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
    virtual void print()
    {
        cout << "Exception: " << str << "; " << what();
    }
};

class WrongBorderValue : public Exception
{
protected:
    int value;

public:
    WrongBorderValue(int val) : Exception("Wrong value of border")
    {
        value = val;
    }

    WrongBorderValue() : Exception("Wrong value of border")
    {
        value = -1;
    }

    WrongBorderValue(const WrongBorderValue &e) : Exception("Wrong value of border")
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
        value = e.value;
    }

    virtual void print()
    {
        cout << "Exception: " << str << "; value of  border: " << value << "; " << what();
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
        cout << "Exception: " << str << "; index 1 : " << index1 << "; "
             << "; index 2 : " << index2 << "; " << what();
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

    virtual ~BaseMatrix()
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
        if (row >= height || row < 0 || column >= width || column < 0)
            throw IndexOutOfBounds(row, column);
        return ptr[row][column];
    }

    BaseMatrix Transponse()
    {
        BaseMatrix Res(width, height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                Res.ptr[j][i] = ptr[i][j];

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

class Matrix : public BaseMatrix
{
public:
    Matrix() : BaseMatrix()
    {
        cout << "Matrix default constructor is working" << endl;
    }

    Matrix(int Height, int Width) : BaseMatrix(Height, Width)
    {
        cout << "Matrix constructor is working" << endl;
    }

    virtual ~Matrix()
    {
        cout << "Matrix destructor is working" << endl;
    }

    void randomValues()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ptr[i][j] = rand() % 30;
            }
        }
    }
    void clear(int h, int w)
    {
        if (ptr != NULL || (h == 0 && w == 0))
        {
            for (int i = 0; i < h; i++)
                delete[] ptr[i];
            delete[] ptr;
            ptr = NULL;
        }
    }

    Matrix updateMatrix(int border)
    {
        vector<int> rows(height);
        vector<int> rows_used;
        vector<int> columns(width);
        vector<int> cols_used;

        if (border <= 0)
        {
            throw WrongBorderValue(border);
        }

        for (int i = 0; i < height; i++)
        {
            int rowSum = 0;
            for (int j = 0; j < width; j++)
            {
                rowSum += ptr[i][j];
                columns[j] += ptr[i][j];

                if (columns[j] > border)
                {
                    cols_used.push_back(j);
                }
            }
            if (rowSum > border)
            {
                rows_used.push_back(i);
            }
            rows[i] = rowSum;
        }
        if ((height - rows_used.size() > 0) && (width - cols_used.size() > 0))
        {
            Matrix res(height - rows_used.size(), width - cols_used.size());
            int i_res, j_res;
            i_res = j_res = 0;
            for (int i = 0; i < height; i++)
            {
                if (find(rows_used.begin(), rows_used.end(), i) == rows_used.end() || rows_used.size() == 0)
                {
                    for (int j = 0; j < width; j++)
                    {
                        if (find(cols_used.begin(), cols_used.end(), j) == cols_used.end() || cols_used.size() == 0)
                        {
                            res(i_res, j_res) = ptr[i][j];
                            j_res++;
                        }
                    }
                    j_res = 0;
                    i_res++;
                }
            }
            return res;
        }
        else
        {
            Matrix res(0, 0);
            return res;
        }
    }

    friend ostream &operator<<(ostream &outStream, Matrix &obj)
    {
        outStream << obj.height << " " << obj.width << '\n';
        for (int i = 0; i < obj.height; i++)
        {
            for (int j = 0; j < obj.width; j++)
            {
                if (j == obj.width - 1)
                {
                    outStream << obj.ptr[i][j];
                }
                else
                {
                    outStream << obj.ptr[i][j] << " ";
                }
            }
            outStream << "\n";
        }
        return outStream;
    }
    friend istream &operator>>(istream &inStream, Matrix &obj)
    {
        int height, width;
        inStream >> height >> width;
        if (height != obj.height || width != obj.width)
        {
            obj.clear(obj.height, obj.width);
            obj.width = width;
            obj.height = height;
            obj.ptr = new double *[height];
            for (int i = 0; i < height; i++)
                obj.ptr[i] = new double[width];
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int t;
                inStream >> t;
                obj.ptr[i][j] = t;
            }
        }

        return inStream;
    }
};

int main()
{
    Matrix base(3, 3);
    base.randomValues();
    base.print();
    try
    {
        Matrix newBase = base.updateMatrix(-1);
        newBase.print();
    }
    catch (WrongBorderValue exc)
    {
        exc.print();
    }
    catch (WrongSizeException exc)
    {
        exc.print();
    }
    catch (IndexOutOfBounds exc)
    {
        exc.print();
    }
    catch (...)
    {
        cout << "Something wrong!!" << endl;
    }

    ofstream fout("test.txt");
    if (fout)
    {
        try
        {
            Matrix temp(4, 5);
            temp.randomValues();
            fout << base;
            fout << temp;
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

            Matrix tempMatrix(1, 1);

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

    return 0;
}