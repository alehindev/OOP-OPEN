#include <iostream>

using namespace std;

class BaseString
{
protected:
	char *p;
	int len;
	int capacity;

public:
	BaseString(char *ptr)
	{
		cout << "\nBase Constructor 1\n";
		int i = 0;
		while (ptr[i] != '\0')
		{
			i++;
		}
		if (i < 256)
		{
			capacity = 256;
		}
		else
		{
			capacity = i;
		}
		// capacity = (i < 256) ?  256:i;
		len = i;
		p = new char[capacity];
		for (int i = 0; i < len; i++)
		{
			p[i] = ptr[i];
		}
		p[i] = '\0';
	}

	BaseString(const char *ptr)
	{
		cout << "\nBase Constructor 1\n";
		int i = 0;
		while (ptr[i] != '\0')
		{
			i++;
		}
		/*
		if (i < 256)
		{
			capacity = 256;
		}
		else
		{
			capacity = i;
		}
		*/
		capacity = (i < 256) ? 256 : i;
		len = i;
		p = new char[capacity];
		for (int i = 0; i < len; i++)
		{
			p[i] = ptr[i];
		}
		p[i] = '\0';
	}

	BaseString(int Capacity = 256)
	{
		cout << "\nBase Constructor 0\n";
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
	}

	~BaseString()
	{
		cout << "\nBase Destructor\n";
		if (p != NULL)
			delete[] p;
		len = 0;
	}

	int Length() { return len; }
	int Capacity() { return capacity; }
	//char* get() {return p;}
	char &operator[](int i) { return p[i]; }

	BaseString &operator=(BaseString &s)
	{
		cout << "\nBase Operator = \n";
		if (capacity > s.len)
		{
			len = s.len;
			for (int i = 0; i < s.len; i++)
			{
				p[i] = s[i];
			}
			p[len] = '\0';
		}
		else
		{
			delete[] p;
			capacity = s.capacity;
			len = s.len;
			p = new char[capacity];
			for (int i = 0; i < len; i++)
			{
				p[i] = s[i];
			}
		}
		return *this;
	}

	BaseString(BaseString &s)
	{
		len = s.len;
		capacity = s.capacity;
		p = new char[capacity];
		for (int i = 0; i < len; i++)
		{
			p[i] = s[i];
		}
		p[len] = '\0';
		cout << "\nBase Copy Constructor\n";
	}

	virtual void print()
	{
		int i = 0;
		while (p[i] != '\0')
		{
			cout << p[i];
			i++;
		}
	}
};

class String : public BaseString
{
public:
	String(int Dimension = 256) : BaseString(Dimension)
	{
		cout << "\nString Constructor\n";
	}
	String(char *str) : BaseString(str)
	{
		cout << "\nString Constructor\n";
	}
	String(const char *str) : BaseString(str)
	{
		cout << "\nString Constructor\n";
	}
	String(String &s)
	{
		len = s.len;
		capacity = s.capacity;
		p = new char[capacity];
		for (int i = 0; i < len; i++)
		{
			p[i] = s[i];
		}
		p[len] = '\0';
		cout << "\nString Copy Constructor\n";
	}
	String &operator=(String &s)
	{
		BaseString &str = (BaseString &)(s);
		return (String &)(BaseString::operator=(str));
	}

	String operator+(String s)
	{
		String Res;
		Res.len = len + s.len;
		Res.capacity = max(len + s.len + 1, max(s.capacity, capacity));
		Res.p = new char[Res.capacity];
		for (int i = 0; i < Res.len; i++)
		{
			if (i < len)
			{
				Res.p[i] = p[i];
			}
			else
			{
				Res.p[i] = s.p[i % len];
			}
		}
		return Res;
	}

	bool IsPalindrome()
	{
		char *p1 = p;
		char *p2 = &p[len - 1];
		while (p1 < p2)
		{
			if (*p1 != *p2)
			{
				return false;
			}
			*p1++;
			*p2++;
		}
		return true;
	}

	int LastIndexOf(String &s)
	{
		int index = 0;
		bool fl = false;
		for (int i = 0; i < len; i++)
		{
			if (p[i] == s[0])
			{
				fl = true;
				for (int j = 0; j < s.len; j++)
				{
					if (s[j] != p[i + j])
					{
						fl = false;
					}
				}
				if (fl)
				{
					index = i;
				}
			}
		}
		if (!fl)
		{
			return -1;
		}
		else
		{
			return index;
		}
	}
};

int main()
{

	char str[] = "test";
	BaseString s1(str);
	BaseString s2("test");
	s1.print();
	s2.print();
	BaseString s3 = s1;
	s3.print();
	s2 = s3;
	s2.print();
	String s4("tetextte");
	String s5("tete");
	cout << "Last index of substr: " << s4.LastIndexOf(s5) << endl;
	return 0;
}
