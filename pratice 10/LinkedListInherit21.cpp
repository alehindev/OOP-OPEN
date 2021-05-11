// LinkedListInherit21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
using namespace std;

#include <iostream>

template <class T>
class Element
{
	//protected:
public:
	//переместить в protected
	Element *next;
	Element *prev;
	T info;

	Element(T data)
	{
		next = prev = NULL;
		info = data;
	}

	Element(Element *Next, Element *Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}

	Element(const Element &el)
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}

	template <class T1>
	friend ostream &operator<<(ostream &s, Element<T1> &el);
};

template <class T1>
ostream &operator<<(ostream &s, Element<T1> &el)
{
	s << el.info;
	return s;
}

template <class T>
class LinkedList
{
	//protected:
public:
	//переместить в protected
	Element<T> *head;
	Element<T> *tail;
	int count;

	LinkedList()
	{
		head = tail = NULL;
		count = 0;
	}

	LinkedList(T *arr, int len)
	{
		//...
	}

	virtual Element<T> *pop() = 0;
	virtual Element<T> *push(T value) = 0;

	Element<T> &operator[](int index)
	{
		//if(index<0 || index>=count) throw ?;

		Element<T> *current = head;

		for (int i = 0;
			 current != NULL && i < index;
			 current = current->next, i++)
			;

		return *current;
	}

	virtual bool isEmpty() { return (LinkedList<T>::count == 0); }

	template <class T1>
	friend ostream &operator<<(ostream &s, LinkedList<T1> &el);

	virtual ~LinkedList()
	{
		cout << "\nBase class destructor";
	}
};

template <class T1>
ostream &operator<<(ostream &s, LinkedList<T1> &el)
{
	Element<T1> *current;
	for (current = el.head; current != NULL; current = current->next)
		s << *current << "; ";
	return s;
}

template <class T>
class Queue : public LinkedList<T>
{
public:
	Queue<T>() : LinkedList<T>()
	{
		LinkedList<T>::head = LinkedList<T>::tail = NULL;
		LinkedList<T>::count = 0;
	}

	virtual ~Queue()
	{

		while (LinkedList<T>::head != NULL)
		{
			Element<T> *temp = LinkedList<T>::head->next;
			delete LinkedList<T>::head;
			LinkedList<T>::head = temp;
		}
		LinkedList<T>::tail = LinkedList<T>::head = NULL;
		LinkedList<T>::count = 0;
		cout << "Child destructor";
	}

	virtual Element<T> *push(T value)
	{
		if (LinkedList<T>::tail == NULL)
		{
			LinkedList<T>::head = new Element<T>(value);
			LinkedList<T>::tail = LinkedList<T>::head;
		}
		else
		{
			LinkedList<T>::tail->next = new Element<T>(value);
			LinkedList<T>::tail->next->prev = LinkedList<T>::tail;
			LinkedList<T>::tail = LinkedList<T>::tail->next;
		}
		LinkedList<T>::count++;
		return LinkedList<T>::tail;
	}
	virtual Element<T> *pop()
	{

		Element<T> *res = LinkedList<T>::head;
		if (LinkedList<T>::head != NULL)
		{
			if (LinkedList<T>::head->next != NULL)
			{
				LinkedList<T>::head = LinkedList<T>::head->next;
				LinkedList<T>::head->prev = NULL;
				res->next = NULL;
			}
			else
			{
				LinkedList<T>::head = LinkedList<T>::tail = NULL;
			}
			LinkedList<T>::count--;
		}
		return res;
	}
	void Filter(Queue<T> *Res, bool (*ptr)(T))
	{
		Element<T> *help = LinkedList<T>::head;
		while (help != NULL)
		{
			if (ptr(help))
			{
				Res->push(help->info);
			}
			help = help->next;
		}
	}
};

bool f(int el)
{
	return true;
}

template <class T>
bool predicate(Element<T> *cur)
{
	if (cur != NULL && cur->info > 0)
	{
		return true;
	}
	return false;
}

class my_class
{
public:
	int data;
	my_class(int v = 0) { data = v; }

	~my_class() { cout << "\nmy_class destructor"; }

	friend ostream &operator<<(ostream &s, my_class &value);
};

ostream &operator<<(ostream &s, my_class &value)
{
	s << value.data;
	return s;
}

double integral(double (*ptr)(double), double left, double right, double step = 0.001)
{
	double x = left;
	double sum = 0;
	while (x < right)
	{
		sum += step * ptr(x);
		x += step;
	}
	return sum;
}

int main()
{
	bool (*ptr)(int);
	ptr = f;

	if (true)
	{
		Queue<int> I;
		Queue<int> Res;
		for (int i = -10; i < 10; i++)
		{
			I.push(i);
		}
		I.Filter(&Res, predicate<int>);
		while (Res.head != NULL)
		{
			Element<int> *help = Res.head->next;
			cout << Res.pop()->info << ' ';
		}
	}

	if (true)
	{
		cout << "Only object\n";
		Queue<int> Q;
		for (int i = 0; i < 100; i += 5)
			Q.push(i);
		for (; !Q.isEmpty(); cout << Q.pop()->info << ", ")
			;
		cout << "\n";
	}

	if (true)
	{
		cout << "\nBase pointer 1\n";
		LinkedList<int> *ptr = new Queue<int>;
		for (int i = 1; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
		//добавить виртуальные деструкторы
	}

	if (true)
	{
		cout << "\nBase pointer 2\n";
		LinkedList<int> *ptr;
		Queue<int> *ptr2 = new Queue<int>;
		ptr = ptr2;
		for (int i = 1; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
		//добавить виртуальные деструкторы
	}

	if (true)
	{
		cout << "\nQueue pointer\n";
		Queue<int> *ptr = new Queue<int>;
		for (int i = 2; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
	}

	/*if (true)
	{
		cout << "\nmy_class Queue test\n";
		Queue<my_class> Q;
		for (int i = 3; i < 100; i += 5)
			Q.push(my_class(i));
		cout << Q;
	}*/

	char c;
	cin >> c;
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
