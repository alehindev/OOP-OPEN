using namespace std;

#include <iostream>

class P
{
public:
	P()
	{
	}
	virtual int getValue() { return 7; }
};

class C : public P
{
public:
	C() {}
	double getValue()
	{
		return 9.68;
	}
};

int main()
{

	C a;
	cout << a.getValue() << endl;
	return 0;
}