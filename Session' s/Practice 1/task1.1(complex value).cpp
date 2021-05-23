#include <iostream>
using namespace std;

class Complex
{
private:
    double real;
    double image;

public:
    Complex()
    {
        real = 0;
        image = 0;
    }
    Complex(double rl)
    {
        real = rl;
        image = 0;
    }
    Complex(double rl, double img)
    {
        real = rl;
        image = img;
    }
    Complex operator*(Complex newComplex)
    {
        Complex res;

        res.real = real * newComplex.real - image * newComplex.image;
        res.image = image * newComplex.real + real * newComplex.image;

        return res;
    }

    Complex operator+()
    {
        Complex res;
        res.real = real;
        res.image = -image;
        return res;
    }

    void Set(double rl, double img)
    {
        real = rl;
        image = img;
    }

    void SetReal(double rl)
    {
        real = rl;
    }

    void SetImage(double img)
    {
        image = img;
    }

    pair<double, double> Get()
    {
        return make_pair(real, image);
    }

    double GetReal()
    {
        return real;
    }

    double GetImage()
    {
        return image;
    }

    void print()
    {
        bool fl = false;
        if (real != 0 || (image == 0 && real == 0))
        {
            cout << real;
            fl = true;
        }
        if (image != 0)
        {
            if (image > 0)
            {
                if (fl)
                {
                    cout << " + ";
                }
                if (image != 1)
                {
                    cout << image;
                }
                cout << 'i';
            }
            else
            {
                cout << " - ";
                if (image != -1)
                {
                    cout << abs(image);
                }
                cout << 'i';
            }
        }
    }
};

void printAxB(Complex A, Complex B)
{
    cout << "Результат умножения числа A(";
    A.print();
    cout << ") на число B(";
    B.print();
    cout << "): \n";
    Complex res = A * B;
    res.print();
    cout << endl;
}
int main()
{
    Complex A(1, 0), B(-1, -8.666);
    Complex C;
    printAxB(A, B);
    A.SetReal(-1);
    A.SetImage(-2);
    B.Set(2, -3);
    printAxB(A, B);
    A.Set(0, -1);
    B.Set(0, -5);
    printAxB(A, B);
    +A;
    cout << "Результат сопряжения: \n";
    A.print();
    cout << endl;
    +B;
    cout << "Результат сопряжения: \n";
    B.print();
    cout << endl;
}