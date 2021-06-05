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

class IndexOutOfBound : public Exception
{
private:
    int index;

public:
    IndexOutOfBound() : Exception("Wrong index")
    {
        index = -1;
    }

    IndexOutOfBound(int i) : Exception("Wrong index")
    {
        index = i;
    }
    IndexOutOfBound(const IndexOutOfBound &e) : Exception("Wrong size")
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
        index = e.index;
    }

    virtual void print()
    {
        cout << "Exception: " << str << "; index: " << index << "; ";
    }
};
class ArrayIsFilled : public Exception
{
public:
    ArrayIsFilled() : Exception("Array is full")
    {
    }
    ArrayIsFilled(const ArrayIsFilled &e) : Exception("Array is full")
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }

    virtual void print()
    {
        cout << "Exception: " << str << "; ";
    }
};
class NoObjects : public Exception
{
public:
    NoObjects() : Exception("No more elemnts in array")
    {
    }
    NoObjects(const NoObjects &e) : Exception("No more elemnts in array")
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }

    virtual void print()
    {
        cout << "Exception: " << str << "; ";
    }
};
template <class T>
class MyArrayParentTemplate
{
protected:
    //сколько памяти выделено?
    int capacity;
    //количество элементов - сколько памяти используем
    int count;
    //массив
    T *ptr;

public:
    //конструкторы и деструктор
    MyArrayParentTemplate(int Dimension = 100)
    {
        cout << "\nMyArrayParentTemplate constructor";
        ptr = new T[Dimension];
        capacity = Dimension;
        count = 0;
    }

    //деструктор
    ~MyArrayParentTemplate()
    {
        if (ptr != NULL)
        {
            delete[] ptr;
            ptr = NULL;
        }
        cout << "\nMyArrayParentTemplate destructor";
    }

    //обращение к полям
    int Capacity() { return capacity; }
    int Size() { return count; }

    T &operator[](int index)
    {
        if (index >= capacity || index < 0)
        {
            throw IndexOutOfBound(index);
        }

        return ptr[index];
    }

    //добавление нового значения
    virtual void push(T value) = 0;
    //удаление элемента
    virtual T pop() = 0;
    void print()
    {
        for (int i = 0; i < count; i++)
        {
            cout << ptr[i] << " ";
        }
        cout << endl;
    }
};

template <class T1>
class myArray : public MyArrayParentTemplate<T1>
{
public:
    myArray<T1>(int Cap = 100) : MyArrayParentTemplate<T1>(Cap)
    {
        cout << endl
             << "Array constructor" << endl;
    }
    ~myArray<T1>()
    {
        cout << endl
             << "Array destructor" << endl;
    }
    void push(T1 val)
    {
        if (MyArrayParentTemplate<T1>::count >= MyArrayParentTemplate<T1>::capacity)
        {
            throw ArrayIsFilled();
        }
        else
        {
            MyArrayParentTemplate<T1>::ptr[MyArrayParentTemplate<T1>::count] = val;
            MyArrayParentTemplate<T1>::count++;
        }
    }
    T1 pop()
    {
        T1 temp;
        if (MyArrayParentTemplate<T1>:: count > 1)
        {
            temp = MyArrayParentTemplate<T1>::ptr[MyArrayParentTemplate<T1>::count - 1];
            MyArrayParentTemplate<T1>::count--;
            return temp;
        }
        else
        {
            throw NoObjects();
        }
    }
};

int main()
{
    myArray<int> array(10);
    for (int i = 0; i < 10; i++)
    {
        array.push(i);
    }
    array.print();
    array.pop();
    array.print();
    cout << endl
         << array[0] << " " << array[1] << " " << endl;
    try
    {
        array[-1] = 0;
    }
    catch (IndexOutOfBound exc)
    {
        exc.print();
    }
    catch (...)
    {
        cout << "Something went wrong!" << endl;
    }
    return 0;
}