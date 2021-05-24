// LinkedListInherit21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
using namespace std;

#include <iostream>
#include <bits/stdc++.h>

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

template <class T>
class Element
{
protected:
public:
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
protected:
public:
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
        head = arr;
        count = len;
    }

    virtual Element<T> *pop() = 0;
    virtual Element<T> *push(T value) = 0;

    Element<T> &operator[](int index)
    {
        if (index < 0 || index >= count)
            throw Exception("Wrong Index");

        Element<T> *current = head;

        for (int i = 0; current != NULL && i < index; current = current->next, i++)
            ;

        return *current;
    }

    virtual bool isEmpty()
    {

        return (LinkedList<T>::count == 0);
    }

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
        s << *current;
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
        if (LinkedList<T>::head == NULL)
        {
            LinkedList<T>::head = new Element<T>(value);
            LinkedList<T>::tail = NULL;
        }
        else
        {
            LinkedList<T>::head->prev = new Element<T>(value);
            LinkedList<T>::head->prev->next = LinkedList<T>::head;
            LinkedList<T>::head = LinkedList<T>::head->prev;
        }
        LinkedList<T>::count++;
        return LinkedList<T>::head;
    }
    virtual Element<T> *pop()
    {

        Element<T> *res = LinkedList<T>::head;
        if (LinkedList<T>::head != NULL)
        {
            if (LinkedList<T>::head->next != NULL)
            {
                LinkedList<T>::head = LinkedList<T>::head->next;
                LinkedList<T>::head->prev = LinkedList<T>::tail;
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
    void Filter(Queue<T> *Res)
    {
        Element<T> *help = LinkedList<T>::head;
        while (help != NULL)
        {
            if (help->info.getSquare() == "Red Square")
            {
                Res->push(help->info);
            }
            help = help->next;
        }
    }

    void modifedFilter(Queue<T> *Res, bool (*ptr)(T value))
    {
        Element<T> *help = LinkedList<T>::head;
        while (help != NULL)
        {
            if (ptr(help->info))
            {
                Res->push(help->info);
            }
            help = help->next;
        }
    };

    Element<T> *find(T value)
    {
        Element<T> *help = LinkedList<T>::head;
        while (help != NULL)
        {
            if (typeid(help->info) == typeid(T) && help->info == value)
            {
                return help;
            }
            help = help->next;
        }
        return NULL;
    }
    void print()
    {
        cout << this[0];
    }

    bool save(string s)
    {
        ofstream fout(s);
        if (fout.is_open())
        {
            fout << "dsakdjalkjsklflkjasjfk";
            fout << this[0];
            fout.close();
            return true;
        }
        return false;
    }
    /*
    virtual Element<T> *insert(T value)
    {
        Element<T> temp(value);
        int pos = rand() % LinkedList<T>::count;
        if (pos == 0 || LinkedList<T>::count == 0)
        {
            return this->push(value);
        }
        else if (pos == LinkedList<T>::count - 1)
        {
            

            temp.prev = LinkedList<T>::tail;
            LinkedList<T>::tail->next = &temp;
            LinkedList<T>::tail = &temp;
            return &temp;
        }
        else
        {
            Element<T> *ptr = &temp;
            cout << this->operator[pos];
            return ptr;
        }
    }*/
    /*
    virtual void remove()
    {

        int pos = rand() % LinkedList<T>::count;
        if (pos == 0 || LinkedList<T>::count == 1)
        {
            this.pop();
        }
        else if (pos == LinkedList<T>::count - 1)
        {

            LinkedList<T>::tail->prev->next = NULL;
            LinkedList<T>::tail = LinkedList<T>::tail->prev;
        }
        else
        {
            Element<T> *el = this[pop];
            el->next->prev = el->prev;
            el->prev->next = el->next;
            delete el;
        }
    }
    */
};

bool f(int el)
{
    return true;
}
/*
template <class T>
bool predicate(Element<T> *cur)
{
	if (cur != NULL && cur->info > 0)
	{
		return true;
	}
	return false;
}
*/

class goverment
{
protected:
    string name, capital, lang, square;
    unsigned int population;

public:
    goverment()
    {
        name = capital = lang = square = "";
        population = 0;
    }
    goverment(string Name, string Capital, string Lang, string Square, unsigned int Population)
    {
        name = Name;
        capital = Capital;
        lang = Lang;
        square = Square;
        population = Population;
    }
    friend ostream &operator<<(ostream &s, goverment &value)
    {
        s << endl;
        s << "Name of country: " << value.name << endl;
        s << "Capital of country: " << value.capital << endl;
        s << "Language of country: " << value.lang << endl;
        s << "Main square of country: " << value.square << endl;
        s << "Population of country: " << value.population << endl;
        s << endl;
        return s;
    }
    string getSquare()
    {
        return square;
    }
    bool operator==(goverment el)
    {
        return (lang == el.lang && name == el.name && capital == el.capital && square == el.square && population == el.population);
    }
    friend bool someFunction(goverment value);
};

bool someFunction(goverment value)
{
    if (value.capital == "Moscow")
    {
        return true;
    }
    return false;
}

int main()
{

    goverment Russia("Russia", "Moscow", "Russian", "Red Square", 145000000);
    goverment Usa("Usa", "Washington", "English", "Times Square", 369000000);
    goverment China("China", "Pekin", "Chinese", "Tiananmen Square", 1500000000);
    goverment Belarus("Belarus", "Minsk", "Russian", "October Square", 369000000);

    Queue<goverment> myQueue;
    Queue<goverment> myFilteredQueue;
    Queue<goverment> myModFilteredQueue;

    cout << "--------- Push test ---------" << endl;

    myQueue.push(Russia);
    myQueue.push(Usa);
    myQueue.push(China);
    myQueue.push(Belarus);
    myQueue.print();

    cout << "--------- Pop test ---------" << endl;
    myQueue.pop();
    myQueue.print();

    cout << "--------- Find test ---------" << endl;

    cout << *myQueue.find(Russia) << endl;

    cout << "--------- Filter test ---------" << endl;

    myQueue.Filter(&myFilteredQueue);
    myFilteredQueue.print();

    cout << "--------- ModifedFilter test ---------" << endl;
    bool (*predicateptr)(goverment value);

    predicateptr = someFunction;

    myQueue.modifedFilter(&myModFilteredQueue, predicateptr);

    myModFilteredQueue.print();

    cout << "--------- Saving test ---------" << endl;
    //myQueue.save("test.txt");
    ofstream fout("test.txt");
    if (fout.is_open())
    {
        fout << "dsakdjalkjsklflkjasjfk";

        fout.close();
    }

    cout << "--------- Loading test ---------" << endl;

    return 0;
}
