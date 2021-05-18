#include <iostream>

using namespace std;

class A1
{
protected:
    int a1;

public:
    A1()
    {
        cout << "\nClass A1 constructor";
    }
    A1(int V1)
    {
        A1::a1 = V1;
        cout << "\nClass A1 constructor modifed";
    }
    virtual void print()
    {
        cout << "\nVariable of A1 class";
    }
    virtual void show()
    {

        cout << "\na1 = " << a1;
    }
};

class B1 : virtual public A1
{
protected:
    int b1;

public:
    B1(int V1 = 0, int V2 = 0) : A1(V2)
    {
        b1 = V1;
        cout << "\nClass B1 constructor ";
    }
    virtual void print()
    {
        cout << "\nVariable of B1 class";
    }
    virtual void show() { cout << "\nb1 = " << b1 << ", a1 = " << a1; }
};
class B2 : virtual public A1
{
protected:
    int b2;

public:
    B2(int V1 = 0, int V2 = 0) : A1(V2)
    {
        b2 = V1;
        cout << "\nClass B2 constructor ";
    }
    virtual void print()
    {
        cout << "\nVariable of B2 class";
    }
    virtual void show()
    {
        cout << "\nb2 = " << b2 << ", a1 = " << a1;
    }
};

class C1 : virtual public B1, virtual public B2
{
protected:
    double c1;

public:
    C1()
    {
        cout << "\nC1 constuctor working";
    }
    C1(double a, double b, double c) : B1(b, a), B2(b, a)
    {
        c1 = c;
        cout << "\nC1 constuctor working";
    }

    virtual void print()
    {

        cout << "\nVariable of C1 class";
    }
    virtual void show()
    {
        cout << '\n'
             << "a1 = " << B1::a1 << '\n';
        cout << "b1 = " << b1 << '\n';
        cout << "b2 = " << b2 << '\n';
        cout << "c1 = " << c1 << '\n';
    }
};

int main()
{
    if (true)
    {
        C1 c(1, 2, 3);
        c.print();
        c.show();
    }
}