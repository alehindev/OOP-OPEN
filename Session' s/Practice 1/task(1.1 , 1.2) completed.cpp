#include <iostream>
#include "bits/stdc++.h"

using namespace std;

class Complex
{
protected:
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

    Complex operator+(Complex q)
    {
        Complex res;
        res.real = real + q.real;
        res.image = image + q.image;
        return res;
    }

    Complex operator+()
    {
        Complex res;
        res.real = real;
        res.image = -image;
        return res;
    }

    friend Complex operator+(double real, Complex complex);

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
/*
Complex operator/(double d, Complex z)
{
    Complex res;
    res.SetReal(d * z.GetReal() / sqrt(pow(z.GetReal(), 2) + pow(z.GetImage(), 2)));

}
*/

Complex operator+(double d, Complex complex)
{
    Complex res;
    res.real = complex.real + d;
    res.image = complex.image;
    return res;
}

class MultiComplex : public Complex
{
public:
    MultiComplex(double rl, double img) : Complex(rl, img){};
    MultiComplex() : Complex() {}
    friend MultiComplex operator*(double d, Complex z);
};
MultiComplex operator*(double d, Complex z)
{
    MultiComplex res;
    res.real = d * z.GetReal();
    res.image = d * z.GetImage();
    return res;
}

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
    Complex NewPlus(1, 0);
    NewPlus = 1 + NewPlus;
    NewPlus.print();
    NewPlus = NewPlus + 1;
    cout << "\n";
    NewPlus.print();
    cout << "\n";
    Complex amount_complex(1, 1);
    MultiComplex amount;
    amount = -1 * amount_complex;
    cout << "\nЗначения от умножения: ";
    amount.print();
}