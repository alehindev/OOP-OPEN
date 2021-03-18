#include <iostream>
using namespace std;
class A1
{
protected:
    int a1;

public:
    A1(int V1 = 0)
    {
        a1 = V1;
        cout << "\nClass A1 constructor";
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
    virtual void
    print()
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
    virtual void
    print()
    {
        cout << "\nVariable of B2 class";
    }
    virtual void show() { cout << "\nb2 = " << b2 << ", a1 = " << a1; }
};

class C1 : public B1, public B2
{
protected:
    int c1;

public:
    void print()
    {
        cout << "\nVariable of C1 class";
    }
    void show()
    {
        cout << "\nc1 = " << c1;
    }
};

int main()
{
    B1 test(1, 2);
    test.show();
    test.print();
    A1 *ptr = &test;
    ptr->show();
    ptr->print();
    char c;
    std::cin >> c;
    return 0;
}