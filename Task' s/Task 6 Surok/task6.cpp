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

template <class T>
class Element
{
protected:
public:
    Element *next;
    Element *prev;
    T info;
    Element()
    {
        next = prev = NULL;
    }
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

    template <class T2>
    friend istream &operator>>(istream &s, Element<T2> &el);
};

template <class T1>
ostream &operator<<(ostream &s, Element<T1> &el)
{
    s << el.info;
    return s;
}

template <class T2>
istream &operator>>(istream &s, Element<T2> &el)
{
    s >> el.info;
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
    template <class T2>
    friend istream &operator>>(istream &s, LinkedList<T2> &el);
    virtual ~LinkedList()
    {
        cout << "\nVirtual Base class destructor";
        Element<T> *current;
        Element<T> *help;
        for (current = head; current != NULL;)
        {
            help = current->next;
            delete current;
            current = help;
        }
        head = NULL;
        tail = NULL;
        count = 0;
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

template <class T2>
istream &operator>>(istream &s, LinkedList<T2> &el)
{
    int count;
    s >> count;
    el.count = count;
    el.head = el.tail = NULL;

    for (int i = 0; i < count; i++)
    {
        Element<T2> temp;
        s >> temp;
        if (el.head == NULL)
        {
            el.head = new Element<T2>(temp.info);
            el.tail = el.head;
        }
        else
        {
            el.tail->next = new Element<T2>(temp.info);
            el.tail->next->prev = el.tail;
            el.tail = el.tail->next;
        }
    }
    return s;
}

template <class T>
class List : public LinkedList<T>
{
public:
    List<T>() : LinkedList<T>()
    {
        LinkedList<T>::head = LinkedList<T>::tail = NULL;
        LinkedList<T>::count = 0;
    }

    virtual ~List()
    {
        while (LinkedList<T>::head != NULL)
        {
            Element<T> *temp = LinkedList<T>::head->next;
            delete LinkedList<T>::head;
            LinkedList<T>::head = temp;
        }
        LinkedList<T>::tail = LinkedList<T>::head = NULL;
        LinkedList<T>::count = 0;
        cout << "Child virtual destructor";
    }

    virtual Element<T> *push(T value)
    {
        if (LinkedList<T>::head == NULL)
        {
            LinkedList<T>::head = new Element<T>(value);
            LinkedList<T>::tail = LinkedList<T>::head;
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

        Element<T> *res = LinkedList<T>::tail;
        if (LinkedList<T>::tail != NULL)
        {
            if (LinkedList<T>::tail->prev != NULL)
            {
                LinkedList<T>::tail = LinkedList<T>::tail->prev;
                LinkedList<T>::tail->next = NULL;
                res->prev = NULL;
            }
            else
            {
                LinkedList<T>::head = LinkedList<T>::tail = NULL;
            }
            LinkedList<T>::count--;
        }
        return res;
    }
    void filter(List<T> *Res)
    {
        Element<T> *help = LinkedList<T>::head;
        while (help != NULL)
        {
            if (help->info.getAdress() == "Surgylov")
            {
                Res->push(help->info);
            }
            help = help->next;
        }
    }

    void modFilter(List<T> *Res, bool (*ptr)(T value))
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
        if (fout)
        {
            fout << this->count;
            fout << this[0];
            fout.close();
            return true;
        }
        return false;
    }

    bool load(string s, List<T> &res)
    {
        ifstream fin(s);
        if (fin)
        {
            fin >> res;
            fin.close();
            return true;
        }
        return false;
    }
};

class person
{
protected:
    string name, surname, adress;
    bool ismale;
    unsigned int tel, data, height;

public:
    person()
    {
        name = surname = adress = "";
        tel = data = height = 0;
        ismale = false;
    }
    person(string Name, string Surname, string Adress, bool Ismale, unsigned int Tel, unsigned int Data, unsigned Height)
    {
        name = Name;
        surname = Surname;
        adress = Adress;
        ismale = Ismale;
        tel = Tel;
        data = Data;
        height = Height;
    }
    friend ostream &operator<<(ostream &s, person &value)
    {
        s << endl;
        s << value.name << endl;
        s << value.surname << endl;
        s << value.adress << endl;
        s << value.ismale << endl;
        s << value.tel << endl;
        s << value.data << endl;
        s << value.height << endl;
        s << endl;
        return s;
    }
    friend istream &operator>>(istream &s, person &value)
    {
        string temp;
        int counter = 0;
        while (getline(s, temp) && counter < 8)
        {
            switch (counter)
            {
            case 1:
                value.name = temp;
                break;
            case 2:
                value.surname = temp;
                break;

            case 3:
                value.adress = temp;
                break;
            case 4:
                if (temp == "true")
                {
                    value.ismale = 1;
                }
                else
                {
                    value.ismale = 0;
                }

                break;
            case 5:
                value.tel = stoi(temp);
                break;
            case 6:
                value.data = stoi(temp);
                break;
            case 7:
                value.height = stoi(temp);
                break;
            default:
                break;
            }
            counter++;
        }
        return s;
    }
    string getSurname()
    {
        return surname;
    }
    string getAdress()
    {
        return adress;
    }
    bool operator==(person el)
    {
        return (el.surname == surname && el.name == name && el.ismale == ismale && el.data == data && el.adress == adress && el.tel == tel && el.height == height);
    }
    friend bool func(person value);
};

bool func(person value)
{
    if (value.name == "Anna")
    {
        return true;
    }
    return false;
}

ostream &manip(ostream &stream)
{
    stream.width(5);
    stream.setf(ios::fixed);
    stream << setfill('0') << setprecision(2);
    return stream;
}

int main()
{
    cout << manip << 0.11 << endl;
    person boy("Vladimir", "Puzin", "Mayakovskaya street", true, 2002316, 21121953, 170);
    person man("Boris", "Eltsin", "Lenina street", 0, 3333333, 4011950, 184);
    person lady("Anna", "Karenina", "Red square", 0, 0, 22122002, 167);
    /*
  cout << boy << endl
       << man << endl
       << lady;
  */

    List<person> listik;
    List<person> listik_updated;
    List<person> listik_mod_updated;
    List<person> loaded_listik;
    listik.push(boy); //push test
    listik.push(man);
    listik.push(lady);
    //listik.print();

    listik.pop(); // pop test

    //listik.print();

    listik.filter(&listik_updated); //filter test
    //listik_updated.print();

    bool (*pre_ptr)(person temp); //mod filter test

    pre_ptr = func;

    listik_updated.modFilter(&listik_mod_updated, pre_ptr);

    //listik_mod_updated.print();

    //cout << *listik.find(lady) << endl; //find test

    listik.save("test.txt"); //writing test

    listik.load("test.txt", loaded_listik);
    loaded_listik.print();

    LinkedList<person> *ptr = new List<person>;
    for (int i = 0; i < 2; i++)
    {
        person t("Boris", "Eltsin", "Lenina street", 0, 3333333, 4011950, i);
        ptr->push(t);
    }
    cout << '\n'
         << *ptr << "\n";
    delete ptr;

    List<person> *ptr1 = new List<person>;
    LinkedList<person> *ptr1_new = dynamic_cast<LinkedList<person> *>(ptr1);
    for (int i = 0; i < 2; i++)
    {
        person t("Boris", "Eltsin", "Lenina street", 0, 3333333, 4011950, i);
        ptr->push(t);
    }
    cout << '\n'
         << *ptr1_new << "\n";
    delete ptr1_new;

    return 0;
}