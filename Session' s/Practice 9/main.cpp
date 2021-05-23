#include <iostream>
#include "bits/stdc++.h"

using namespace std;

template <class T>

class element
{
public:
    element *next;
    element *prev;
    T info;
    element(T data)
    {
        next = prev = NULL;
        info = data;
    }
    element(element *Next, element *Prev, T data)
    {
        next = Next;
        prev = Prev;
        info = data;
    }
    element(const element &el)
    {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }

    template <class T1>
    friend ostream &operator<<(ostream &s, element<T1> &el);

    ~element() {}
};
template <class T1>
ostream &operator<<(ostream &s, element<T1> &el)
{
    s << el.info << ' ';
    return s;
}

template <class T>
class linkedlist
{
public:
    element<T> *head;
    element<T> *tail;
    int count;
    linkedlist()
    {
        head = tail = NULL;
        count = 0;
    }
    linkedlist(T *arr, int len)
    {
        //...;
    }
    virtual element<T> *push_front(T value)
    {
        if (head == NULL)
        {
            head = new element<T>(value);
            tail = head;
        }
        else
        {
            element<T> *temp = new element<T>(value);
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        count++;
        return head;
    }
    virtual element<T> *push_back(T value)
    {
        if (head == NULL)
        {
            head = new element<T>(value);
            tail = head;
        }
        else
        {
            tail->next = new element<T>(value);
            tail->next->prev = tail;
            tail = tail->next;
        }

        count++;
        return tail;
    }
    element<T> &operator[](int index)
    {
        element<T> *current = head;
        for (int i = 0; i < index && current != NULL; current = current->next, i++)
            ;
        return *current;
    }
    template <class T2>
    friend ostream &operator<<(ostream &s, linkedlist<T2> &el);

    void print_r(element<T> *current)
    {
        if (current == NULL)
        {
            return;
        }
        cout << *current;
        print_r(current->next);
    }
    element<T> *find_r(element<T> *current, T toFind)
    {
        if (current == NULL)
        {
            return NULL;
        }
        if (current->info == toFind)
        {
            return current;
        }
        return find_r(current->next, toFind);
    }
    element<T> *find_r2(T toFind, element<T> *current = NULL)
    {
        if (head == NULL)
        {
            return NULL;
        }
        if (current == NULL)
        {
            current = head;
        }
        if (current->info == toFind)
        {
            return current;
        }
        if (current->next != NULL)
        {
            return find_r2(toFind, current->next);
        }
        else
        {
            return NULL;
        }
    }
    void print()
    {
        print_r(head);
    }
    element<T> *insert(element<T> *current, T value)
    {
        if (current == NULL)
        {
            //return push_front(current);
        }
        if (current == tail)
        {
            return push_back(value);
        }

        element<T> *inserted = new element<T>(value);
        element<T> *old_next = current->next;
        current->next = inserted;
        inserted->prev = current;
        inserted->next = old_next;
        old_next->prev = inserted;
        count++;
        return inserted;
    }
};
template <class T2>
ostream &operator<<(ostream &s, linkedlist<T2> &el)
{
    element<T2> *current;

    for (current = el.head; current != NULL; current = current->next)
    {
        s << *current << ", ";
    }
    return s;
}

int main()
{
    linkedlist<int> list;
    for (int i = 0; i < 10; i++)
    {
        list.push_back(i);
    }
    element<int> *current = list.find_r2(2);
    list.insert(current, 43223);
    list.print();
    list.push_front(32);
    list.push_front(-132);
    list.print();
    cout << *list[0].next;
    return 0;
}