#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Element
{
protected:
    Element *prev;
    Element *left;
    Element *right;
    T info;

public:
    Element(T data)
    {
        prev = left = right = NULL;
        info = data;
    }

    Element(Element *Left, Element *Right, Element *Prev, T data)
    {
        left = Left;
        right = Right;
        prev = Prev;
        info = data;
    }

    Element(const Element &el)
    {
        left = el.left;
        right = el.right;
        prev = el.prev;
        info = el.info;
    }

    Element *Left()
    {
        return left;
    }

    Element *Right()
    {
        return right;
    }

    Element *Prev()
    {
        return prev;
    }

    void setLeft(Element *n)
    {
        left = n;
    }

    void setRight(Element *n)
    {
        right = n;
    }

    void setPrev(Element *p)
    {
        prev = p;
    }

    T Info()
    {
        return info;
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
class BinTree
{
protected:
    Element<T> *head;
    int count;
    Element<T> *begin;

    void delete_tree(Element<T> *n)
    {
        if (n->Left() != NULL)
        {
            delete_tree(n->Left());
        }

        if (n->Right() != NULL)
        {
            delete_tree(n->Right());
        }

        delete n;
    }

public:
    BinTree()
    {
        cout << "\nConstructor \n";
        begin = head = NULL;
        count = 0;
    }

    virtual Element<T> *push(T value)
    {
        string s;
        if (head == NULL)
        {
            s += string("h");
            this->head = new Element<T>(value);
            this->begin = this->head;
        }
        else
        {
            s += string("h");
            this->head = this->begin;
            while (this->head != NULL)
            {
                if (value < this->head->Info())
                {
                    s += string("l");
                    if (this->head->Left() == NULL)
                    {
                        this->head->setLeft(new Element<T>(value));
                        this->head = this->head->Left();
                        break;
                    }
                    this->head = this->head->Left();
                }
                else
                {
                    s += string("r");
                    if (this->head->Right() == NULL)
                    {
                        this->head->setRight(new Element<T>(value));
                        this->head = this->head->Right();
                        break;
                    }
                    this->head = this->head->Right();
                }
            }
        }
        cout << this->head->Info() << " " << s << "\n";
        return this->head;
    }

    void min()
    {
        this->head = this->begin;
        while (this->head->Left() != NULL)
        {
            this->head = this->head->Left();
        }
        cout << *this->head << "\n";
    }

    void LCA(int a, int b)
    {
        this->head = this->begin;
        while (this->head != NULL)
        {
            this->head->setPrev(this->head);
            if ((this->head->Info() > a) && (this->head->Info() > b))
                this->head = this->head->Left();
            else if ((this->head->Info() < a) && (this->head->Info() < b))
                this->head = this->head->Right();
            else if ((this->head->Info() == a) || (this->head->Info() == b))
            {
                cout << this->head->Prev() << "\n";
                break;
            }
            else
            {
                cout << this->head->Info() << "\n";
                break;
            }
        }
    }

    void search(int n)
    {
        string s;
        s += string("h");
        this->head = this->begin;
        while ((this->head != NULL) && (this->head->Info() != n))
        {
            if (n < this->head->Info())
            {
                s += string("l");
                this->head = this->head->Left();
            }
            else if (n > this->head->Info())
            {
                s += string("r");
                this->head = this->head->Right();
            }
        }
        if (this->head == NULL)
        {
            cout << "NON"
                 << "\n";
            return;
        }
        cout << s << "\n";
    }

    virtual bool isEmpty() { return (BinTree<T>::count == 0); }

    Element<T> *Head()
    {
        return head;
    }

    int Count()
    {
        return count;
    }

    void incCount(int c)
    {
        count += c;
    }

    template <class T1>
    friend ostream &operator<<(ostream &s, BinTree<T1> &el);

    virtual ~BinTree()
    {
        head = begin;
        cout << "\nVirtual Base class destructor";
        delete_tree(head);
        head = NULL;
        count = 0;
    }
};

template <class T1>
ostream &operator<<(ostream &s, BinTree<T1> &el)
{
    Element<T1> *current;
    for (current = el.head; current != NULL; current = current->Next())
        s << *current << "; ";
    return s;
}

int main()
{
    BinTree<int> B;
    B.push(23);
    B.push(13);
    B.push(47);
    B.push(6);
    B.push(2);
    B.push(51);
    B.push(304);
    B.push(17);
    B.push(7);

    B.min();
    B.LCA(13, 47);
    B.search(6);
    B.search(306);

    char c;
    cin >> c;
    return 0;
}